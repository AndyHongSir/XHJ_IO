//
//  BaseSocket.cpp
//  Syn
//
//  Created by Andy Hong on 2016/12/5.
//
//

#include "cocos2d.h"
#include "BaseSocket.h"



#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <memory>
#include "GSKeyChainDataManager.h"
//#include "syn.pb.h"

#include <google/protobuf/stubs/common.h> // implicit_cast, down_cast
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
//#include <google/protobuf/io/gzip_stream.h>
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "MessageTool.hpp"

//#include "GSKeyChainDataManager.h"

BaseSocket* BaseSocket::m_pInstance = nullptr;

using boost::asio::ip::tcp;
using namespace std;

const int kGateWayLogin =1;
const int kGateWayGame =2;


BaseSocket::BaseSocket()
: _io_service()
, _io_work(new boost::asio::io_service::work(_io_service))
, _is_connecting(false)
, _is_connected(false)
, _stopped(false)
, _is_writing(false)
, _is_auto_connect(false)
, _is_allow_ping(false)
, _is_start(true)
, _is_gateway_change(false)
, _is_need_full_data(true)
, _try_connect_game_server(0)
, _server_port(0)
, _msg_login_auth(new(std::nothrow) jynetwork::proto::SCMessageLoginAuth)
, _gateway_step(kGateWayLogin)
, _func_handle_message(nullptr)
, _is_reconnect(false)
, _ack_opcode(0)
, _ack_opcode_bak(0)
, _ack_operation(0)
, _ack_operation_bak(0)
,_socket(new(std::nothrow) tcp::socket(_io_service))
,_write_msg()
,_read_msg()
{
    _write_msg.SetSession(this);
    _read_msg.SetSession(this);
// _socket(new(std::nothrow) tcp::socket(_io_service));
}

BaseSocket::~BaseSocket()
{
//    _io_work.reset();
    for_each(_io_threads.begin(), _io_threads.end(), std::mem_fn(&std::thread::join));
}

bool BaseSocket::Initialize()
{
    
    _io_threads.emplace_back([this] ()
                             {
                                 //Continue looping despite errors.
                                 //If we successfully leave the run method we return.
                                 while(true)
                                 {
                                     try
                                     {
                                         _io_service.run();
                                         return;
                                     }
                                     catch(...)
                                     {
                                         //                 LogError << "A near fatal exception has occurred.";
                                     }
                                 }
                             });
    return true;
}

void BaseSocket::ConnectDefault(){
//    InnerConnectDefault();
    _io_service.post(boost::bind(&BaseSocket::InnerConnectDefault, this));

}

void BaseSocket::InnerClearListMessages(uint16_t ack_opcode, uint16_t ack_operation)
{
#ifdef __NET_PACKET_DEBUG__
    cocos2d::log("InnerClearListMessages param opcode %d, operation %d", ack_opcode, ack_operation);
#endif
    if (!_message_list.empty()) {
        auto& smc = _message_list.front();
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("InnerClearListMessages start %d, opcode %d, operation %d : stack opcode %d", (int)_message_list.size(), ack_opcode, ack_operation, smc._ack_opcode);
        for (auto it = _message_list.begin(); it != _message_list.end(); ++it) {
            SocketMessageCell& smc = *it;
            cocos2d::log("_message_list _opcode %d, _ack_opcode %d : _ack_operation %d, time %d", smc._opcode, smc._ack_opcode, smc._ack_operation, smc._debug_time);
        }
#endif
        if (smc._ack_opcode == ack_opcode) {
            _message_list.pop_front();
        }
        if (_message_list.size() == 0) {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
//                cocos2d::ActivityIndicatorLayer::HideIndicatorLayer();
            });
        }
        return;
    }
}


bool BaseSocket::HandleMessage(uint16_t opcode, std::shared_ptr< ::google::protobuf::MessageLite>& msg)
{
    if (opcode == jynetwork::proto::eSCMessagePong) {
        return true;
    }
    InnerClearListMessages(opcode, 0);
    if (_func_handle_message) {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([this, opcode, msg] {
            _func_handle_message(this, opcode, msg);
        });
        return true;
    }
    return false;
}


bool BaseSocket::ParseMessage(uint16_t opcode, const void* p0, int size0, const void* p1, int size1)
{
    std::shared_ptr< ::google::protobuf::MessageLite > message;
    if (qj::CreateSMessage(opcode, message))
    {
        if (size1 == 0) {
            if (message->ParsePartialFromArray(p0,size0)) {
                return HandleMessage(opcode, message);
            }
        } else {
            google::protobuf::io::ArrayInputStream input1(p0, size0);
            google::protobuf::io::ArrayInputStream input2(p1, size1);
            google::protobuf::io::ZeroCopyInputStream* streams[] = {&input1, &input2};
            // Create the concatenating stream and read.
            google::protobuf::io::ConcatenatingInputStream input(streams, GOOGLE_ARRAYSIZE(streams));
            if (message->ParsePartialFromBoundedZeroCopyStream(&input, size0+size1)) {
                return HandleMessage(opcode, message);
            }
        }
    }
    return true;
}

void BaseSocket::handle_connect(const boost::system::error_code& ec,
                                tcp::resolver::iterator endpoint_iter){
    if (_stopped) {
        _is_connecting = false;
        _is_connected = false;
        return;
    }
    
    // The async_connect() function automatically opens the socket at the start
    // of the asynchronous operation. If the socket is closed at this time then
    // the timeout handler must have run first.
    if (!_socket->is_open())
    {
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("Connect timed out");
#endif
        
        // Try the next available endpoint.
        start_connect(++endpoint_iter);
    }
    
    // Check if the connect operation failed before the deadline expired.
    else if (ec)
    {
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("Connect error %d: %s", ec.value(), ec.message().c_str());
#endif
        
        // We need to close the socket used in the previous connection attempt
        // before starting a new one.
        _socket->close();
        
        // Try the next available endpoint.
        start_connect(++endpoint_iter);
    }
    
    // Otherwise we have successfully established a connection.
    else
    {
#ifdef __NET_PACKET_DEBUG__
        std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";
#endif
        
        _is_connecting = false;
        _is_connected = true;
        
        // Start the input actor.
        start_read();
        
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([this]{
            this->OnConnect();
        });
    }

    
}

void BaseSocket::HandleLoginAuth(std::shared_ptr<jynetwork::proto::SCMessageLoginAuth> msg)
{
    _io_service.post(boost::bind(&BaseSocket::InnerHandleLoginAuth, this, msg));
}

void BaseSocket::InnerHandleLoginAuth(std::shared_ptr<jynetwork::proto::SCMessageLoginAuth> msg)
{
    auto msg_login_auth = GetSCMessageLoginAuth();
    msg_login_auth->CopyFrom(*(msg.get()));
    
    if (msg_login_auth->has_acc_id() && msg_login_auth->has_session_key() && msg_login_auth->has_port() && msg_login_auth->has_gate_ip()) {
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("HandleLoginAuth session_key: %d", msg_login_auth->session_key());
        if (msg->has_acc_id()) {
            cocos2d::log("acc_id %d", msg->acc_id());
        }
#endif
        SetGatewayStep(kGateWayGame);
    }
    InnerStop();
}

void BaseSocket::OnConnect()
{
    _io_service.post(boost::bind(&BaseSocket::InnerOnConnect, this));
}

void BaseSocket::DirectSend(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> pmsg)
{
    _io_service.post(boost::bind(&BaseSocket::InnerDirectSend, this, opcode, pmsg));
}


void BaseSocket::InnerOnConnect()
{

    
    switch (_gateway_step)
    {
        case kGateWayLogin:
        {
            if (_is_start) {    //登陆账号服务器网关
                std::shared_ptr< ::google::protobuf::MessageLite > msg;
                if (qj::CreateCMessage(jynetwork::proto::eCSMessageLoginAuth, msg)) {
                      std::shared_ptr<jynetwork::proto::CSMessageLoginAuth> pmsg = std::dynamic_pointer_cast<jynetwork::proto::CSMessageLoginAuth>(msg);
                     string _user_name ;//GSKeyChainDataManager::readUUID();
                    #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
                       _user_name = "AABBCCDD";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                    _user_name = cocos2d::StringUtils::format("%s",GSKeyChainDataManager::readUUID()); //std::string(GSKeyChainDataManager::readUUID());
                    cocos2d::log("username = %s",_user_name.c_str());
                    
#endif
                      pmsg->set_user_name(_user_name);
                    _ack_opcode_bak = _ack_opcode;
                    _ack_operation_bak = _ack_operation;
                    _ack_opcode = jynetwork::proto::eSCMessageLoginAuth;
                    InnerDirectSend(jynetwork::proto::eCSMessageLoginAuth, msg);
                    //ClearPoolMessage();
                    _is_start = false;
                    _is_need_full_data = true;

                }


                
            }
        }
            break;
        case kGateWayGame:
        {
            _is_gateway_change = false;
            if (_is_start) {    //登陆游戏服务器网关
                std::shared_ptr< ::google::protobuf::MessageLite > msg;
                if (qj::CreateCMessage(jynetwork::proto::eCSMessageGateAuth, msg)) {
                    std::shared_ptr<jynetwork::proto::CSMessageGateAuth> pmsg = std::dynamic_pointer_cast<jynetwork::proto::CSMessageGateAuth>(msg);
                    pmsg->set_acc_id(_msg_login_auth->acc_id());
#ifdef __NET_PACKET_DEBUG__
                    cocos2d::log("Send CSMessageLoginAuth session_key %d", _msg_login_auth->session_key());
#endif
                    pmsg->set_session_key(_msg_login_auth->session_key());
          
                    _ack_opcode_bak = _ack_opcode;
                    _ack_operation_bak = _ack_operation;
                    _ack_opcode = jynetwork::proto::eSCMessageGateAuth;
                    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
//                        cocos2d::ActivityIndicatorLayer::ShowIndicatorLayer(kIndicatorDurationShort);
                    });
                    InnerDirectSend(jynetwork::proto::eCSMessageGateAuth, msg);
                    //                    ClearPoolMessage();
                    _is_start = false;
                    
                
                }

                
            }
        }
            break;
        default:
            break;
    }
}



void BaseSocket::start_read()
{
#ifdef CHECK_DEAD_LINE
    // Set a deadline for the read operation.
    _deadline.expires_from_now(boost::posix_time::seconds(30));
#endif
    

    _read_msg.Normalize();
//    _read_buffer.EnsureFreeSpace();
    _socket->async_read_some(boost::asio::buffer(_read_msg.GetWritePointer(), _read_msg.GetRemainingSpace()),
                             boost::bind(&BaseSocket::handle_read, this, _1, _2));

    
    
}

void BaseSocket::handle_read(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
    if (_stopped)
        return;
    
    if (!ec)
    {
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("handle_read bytes_transferred: %d", (int)bytes_transferred);
#endif
        bool bsuccess = _read_msg.handleMsg(bytes_transferred);
        if (!bsuccess)
        {
#ifdef __NET_PACKET_DEBUG__
            cocos2d::log("Error on handle_read");
#endif
            stop();
            return;
        }
        start_read();
    }
    else
    {
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("Error on receive %d: %s", ec.value(), ec.message().c_str());
#endif
        
        stop();
    }
}

void BaseSocket::OnDisconnect()
{
    HandleDisconnect();
}

void BaseSocket::Connect(const char* ip, uint32_t port)
{
    _io_service.post(boost::bind(&BaseSocket::InnerConnect, this, ip, port));
}

void BaseSocket::InnerDirectSend(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> pmsg)
{
#ifdef __NET_PACKET_DEBUG__
    cocos2d::log("InnerDirectSend %s", jysvr::GetOpcodeC(opcode).c_str());
#endif
    if (!IsConnected()) {
#ifdef __NET_INDICATOR_DEBUG__
        cocos2d::log("InnerSend IsConnect false");
#endif
        return;
    }
    if (opcode == jynetwork::proto::eCSMessageGateAuth) {
        _write_msg.SendNetMessage(opcode, pmsg.get(), false);
    } else {
        _write_msg.SendNetMessage(opcode, pmsg.get(), true);
    }
    //    _send_msgs.emplace_back(_write_buffer.GetLastSendMsgSequenceId(), std::move(pmsg));
    
    if (!_is_writing) {
        start_write();
    }
}


void BaseSocket::HandleDisconnect(){
//    GlobalSchedule::SetEnablePing(false);
//#ifdef __NET_PACKET_DEBUG__
    cocos2d::log("socket OnDisconnect");
//#endif
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
//        DataDoc *pDoc = DataDoc::getInstance();
//        pDoc->OnNetDisconnect();
    });
    
    if (_is_gateway_change) {
        if (_msg_login_auth->has_gate_ip() && _msg_login_auth->has_port()) {
#ifdef __NET_PACKET_DEBUG__
            cocos2d::log("socket OnDisconnect Connect %s %d", _msg_login_auth->gate_ip().c_str(), _msg_login_auth->port());
#endif
//            GlobalSchedule::start(GLOBAL_SCHEDULE_INTERVAL,GLOBAL_SCHEDULE_INTERVAL);
//#ifdef __NET_INDICATOR_DEBUG__
            cocos2d::log("ShowIndicatorLayer OnDisconnect");
//#endif
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
//                cocos2d::ActivityIndicatorLayer::ShowIndicatorLayer(kIndicatorDurationShort);
            });
            
            Connect(_msg_login_auth->gate_ip().c_str(), _msg_login_auth->port());
        }
        return;
    }
    if (_gateway_step == kGateWayLogin) {
        return;
    }
    if (_is_auto_connect) {
        ReConnect();
    } else {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([&]{
//            if (!Reconnect::ShowReconnectDlg()) {
//                _reconnect_timer.expires_from_now(boost::posix_time::seconds(3));
//                _reconnect_timer.async_wait(boost::bind(&JySocket::InnerReConnect, this));
//                //                this->ReConnect();
//            }
        });
    }
    
}




void BaseSocket::SetGatewayStep(int gateway_step)
{
    if (_gateway_step != gateway_step)
    {
        _is_gateway_change = true;
    }
    _gateway_step = gateway_step;
    if (gateway_step == kGateWayLogin) {
        _is_gateway_change = false;
        auto mla = GetSCMessageLoginAuth();
        mla->Clear();
    }
}


void BaseSocket::SetDefaultConnect(const std::string& address, uint32_t port)
{
    _server_address = address;
    _server_port = port;
#ifdef __NET_PACKET_DEBUG__
    cocos2d::log("SetDefaultConnect %s : %d", _server_address.c_str(), _server_port);
#endif
}



void BaseSocket::InnerConnect(const char* ip, uint32_t port)
{
#ifdef __NET_PACKET_DEBUG__
    cocos2d::log("InnerConnect %s : %d", ip, port);
#endif
    if (_is_connecting || _is_connected) {
        return;
    }
    
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
#ifdef __NET_INDICATOR_DEBUG__
        cocos2d::log("ShowIndicatorLayer InnerConnect");
#endif
       
    });
    _socket.reset(new(std::nothrow) tcp::socket(_io_service));
    tcp::resolver r(_io_service);
    std::stringstream ss;
    ss << port;
    start(r.resolve(tcp::resolver::query(ip, ss.str().c_str())));
}

void BaseSocket::start_connect(tcp::resolver::iterator endpoint_iter)
{
    _is_connecting = true;
    _is_connected = false;
    
    if (endpoint_iter != tcp::resolver::iterator())
    {
#ifdef __NET_PACKET_DEBUG__
        std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";
#endif
        
#ifdef CHECK_DEAD_LINE
        // Set a deadline for the connect operation.
        _deadline.expires_from_now(boost::posix_time::seconds(60));
#endif
        // Start the asynchronous connect operation.
        _socket->async_connect(endpoint_iter->endpoint(),
                               boost::bind(&BaseSocket::handle_connect,
                                           this, _1, endpoint_iter));
    }
    else
    {
        // There are no more endpoints to try. Shut down the client.
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("There are no more endpoints to try. Shut down the client.");
#endif
        stop();
    }
}

void BaseSocket::stop()
{
    _stopped = true;
    _io_service.post(boost::bind(&BaseSocket::InnerStop, this));
}

// This function terminates all the actors to shut down the connection. It
// may be called by the user of the client class, or by the class itself in
// response to graceful termination or an unrecoverable error.
void BaseSocket::InnerStop()
{
    _is_connecting = false;
    _is_connected = false;
    _stopped = true;
    _is_writing = false;
    _is_start = true;
    
    //    boost::system::error_code ec_shutdown;
    //    _socket->shutdown(boost::asio::socket_base::shutdown_both, ec_shutdown);
    boost::system::error_code error;
    _socket->close(error);
    
#ifdef CHECK_DEAD_LINE
    _deadline.cancel();
#endif
    //    _heartbeat_timer.cancel();
//    _reconnect_timer.cancel();
//    
//    _read_buffer.reset();
//    _read_buffer.ResetCrypto();
//    _write_buffer.reset();
//    _write_buffer.ResetCrypto();
//    
    _is_start = true;
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([this]{
        this->OnDisconnect();
    });
}


// Called by the user of the client class to initiate the connection process.
// The endpoint iterator will have been obtained using a tcp::resolver.
void BaseSocket::start(tcp::resolver::iterator endpoint_iter)
{
    _stopped = false;
    _is_writing = false;
    _is_start = true;
    
    // Start the connect actor.
    start_connect(endpoint_iter);
    
    // Start the deadline actor. You will note that we're not setting any
    // particular deadline here. Instead, the connect and input actors will
    // update the deadline prior to each asynchronous operation.
#ifdef CHECK_DEAD_LINE
    _deadline.async_wait(boost::bind(&BaseSocket::check_deadline, this));
#endif
}


void BaseSocket::InnerConnectDefault(){
    try
    {
        
        if (_is_connecting || _is_connected) {
            return;
        }
        
        auto mla = GetSCMessageLoginAuth();
        if (mla->has_acc_id() && mla->has_session_key() && mla->has_port() && mla->has_gate_ip()) {
            _is_start = true;
            SetGatewayStep(kGateWayGame);
            InnerConnect(mla->gate_ip().c_str(), mla->port());
        } else {
            _is_start = true;
            SetGatewayStep(kGateWayLogin);
            InnerConnect(_server_address.c_str(), _server_port);
        }

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void BaseSocket::Send(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> pmsg, uint16_t ack_opcode, uint16_t ack_operation)
{
    _io_service.post(boost::bind(&BaseSocket::InnerSend, this, opcode, pmsg, ack_opcode, ack_operation));
}

bool BaseSocket::IsConnected(){
    return _is_connected;
}

void BaseSocket::ReConnect()
{
    _io_service.post(boost::bind(&BaseSocket::InnerReConnect, this));
}

void BaseSocket::InnerReConnect()
{
    _is_reconnect = true;

    CloseAll();
    ConnectDefault();
}

void BaseSocket::CloseAll()
{
    _is_auto_connect = false;
    _is_allow_ping = false;
    _is_start = true;
    _is_gateway_change = false;
    stop();
}
void BaseSocket::start_write()
{
    if (_stopped)
        return;
    if (_is_writing) {
        return;
    }

    std::size_t bytesToSend = _write_msg.GetSize();
    if (bytesToSend == 0) {
        return;
    }
    _is_writing = true;
    _socket->async_write_some(boost::asio::buffer(_write_msg.GetReadPointer(), bytesToSend), boost::bind(&BaseSocket::handle_write, this, _1, _2));
}
void BaseSocket::handle_write(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
    if (_stopped)
        return;
    
    if (!ec)
    {
        bool bsucessed = _write_msg.handleWriteMsg(bytes_transferred);
        if (!bsucessed)
        {
#ifdef __NET_PACKET_DEBUG__
            cocos2d::log("handle_write: fail!");
#endif
            stop();
            return;
        }
        _is_writing = false;
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("handle_write: %d", (int)bytes_transferred);
#endif
        
        if (_write_msg.GetSize() > 0) {
            start_write();
        }
    }
    else
    {
#ifdef __NET_PACKET_DEBUG__
        cocos2d::log("Error on write %d: %s", ec.value(), ec.message().c_str());
#endif
        
        stop();
    }
}

void BaseSocket::InnerSend(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> pmsg, uint16_t ack_opcode, uint16_t ack_operation)
{
    if ((ack_opcode == 0)&&(ack_operation == 0)) {
        InnerDirectSend(opcode, pmsg);
        return;
    }
    
    if (!IsConnected()) {
#ifdef __NET_INDICATOR_DEBUG__
        cocos2d::log("InnerSend ConnectDefault");
#endif
        ReConnect();
        return;
    }
    bool is_need_insert = true;
    if (!_message_list.empty()) {
        auto& cell = _message_list.back();
        if (cell._opcode == opcode) {
            int len = pmsg->ByteSize();
            if (cell._msg->ByteSize() == len) {
                std::vector<unsigned char> sbuf1;
                sbuf1.resize(len);
                std::vector<unsigned char> sbuf2;
                sbuf2.resize(len);
                pmsg->SerializeToArray(reinterpret_cast<void*>(sbuf1.data()), len);
                cell._msg->SerializeToArray(reinterpret_cast<void*>(sbuf2.data()), len);
                if (memcmp(sbuf1.data(), sbuf2.data(), len) == 0) {
                    is_need_insert = false;
                }
            }
        }
    }

    if (is_need_insert) {
        //#ifdef __NET_PACKET_DEBUG__
        //        cocos2d::log("InnerSend %s, waiting opcode %d, operation %d", jysvr::GetOpcodeC(opcode).c_str(), ack_opcode, ack_operation);
        //#endif
        _write_msg.SendNetMessage(opcode, pmsg.get(), true);
        if (!_is_writing) {
            start_write();
        }
    } else {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
//            cocos2d::ActivityIndicatorLayer::ShowIndicatorLayer(kIndicatorDurationShort);
        });
    }
}


BaseSocket* BaseSocket::getInstance()
{
    if ( m_pInstance == nullptr ) {

//        boost::asio::io_service _io_service;
        m_pInstance = new(std::nothrow) BaseSocket();
        
        
        m_pInstance->Initialize();
        //        std::thread work_thread(std::bind(&boost::asio::io_service::run, &(m_pInstance->GetIoService())));
    }
    return m_pInstance;
}

