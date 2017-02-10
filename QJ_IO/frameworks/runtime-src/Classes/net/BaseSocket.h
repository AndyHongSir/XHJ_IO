//
//  BaseSocket.hpp
//  Syn
//
//  Created by Andy Hong on 2016/12/5.
//
//

#ifndef BaseSocket_h
#define BaseSocket_h

#pragma once

#include <boost/asio.hpp>

#include "chat_message.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

#include "CSMessage.pb.h"
#include "SCMessage.pb.h"
#include "BaseMessage.h"
using boost::asio::deadline_timer;
using boost::asio::ip::tcp;

#include <list>
#include <thread>

struct SocketMessageCell
{
    uint16_t _opcode;
    std::shared_ptr<::google::protobuf::MessageLite> _msg;
    uint16_t _ack_opcode;
    uint16_t _ack_operation;
#ifdef __NET_PACKET_DEBUG__
    uint32_t _debug_time;
#endif
    
    SocketMessageCell(uint16_t opcode, std::shared_ptr< ::google::protobuf::MessageLite>& msg, uint16_t ack_opcode, uint16_t ack_operation)
    : _opcode(opcode)
    , _msg(msg)
    , _ack_opcode(ack_opcode)
    , _ack_operation(ack_operation)
    {
#ifdef __NET_PACKET_DEBUG__
        _debug_time = GetUTCtime();
#endif
    }
};

class BaseSocket : public BaseSession

{
public:
    BaseSocket();
    virtual ~BaseSocket();
    static BaseSocket* getInstance();
    virtual void stop() override;
    virtual bool HandleMessage(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite>& msg) override;
    virtual bool ParseMessage(uint16_t opcode, const void* p0, int size0, const void* p1, int size1) override;
    virtual void OnConnect() override;
    virtual void OnDisconnect() override;
    
    void Send(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> pmsg, uint16_t ack_opcode, uint16_t ack_operation);
    void DirectSend(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> pmsg);
    void InnerSend(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> pmsg, uint16_t ack_opcode, uint16_t ack_operation);
    void InnerDirectSend(uint16_t opcode, std::shared_ptr<::google::protobuf::MessageLite> pmsg);
    
    void SetDefaultConnect(const std::string& address, uint32_t port);
    bool Initialize();
    void ConnectDefault();
    void InnerConnectDefault();
    void HandleLoginAuth(std::shared_ptr<jynetwork::proto::SCMessageLoginAuth> msg);
    

    
    void SetHandleMessage(const std::function<bool(BaseSocket*, uint16_t, std::shared_ptr<::google::protobuf::MessageLite>)> &func) { _func_handle_message = func; }
    
    boost::asio::io_service _io_service;
    void Connect(const char* ip, uint32_t port);
private:
    void InnerHandleLoginAuth(std::shared_ptr<jynetwork::proto::SCMessageLoginAuth> msg);
    void HandleDisconnect();
    void InnerClearListMessages(uint16_t ack_opcode, uint16_t ack_operation);
    void handle_write(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void start_write();
    void CloseAll();
    void ReConnect();
    void InnerReConnect();
    bool IsConnected();
    void InnerOnConnect();
    void start_read();
    void handle_read(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void InnerStop();
    void start_connect(tcp::resolver::iterator endpoint_iter);
    void start(tcp::resolver::iterator endpoint_iter);
    void InnerConnect(const char* ip, uint32_t port);
    void SetGatewayStep(int gateway_step);
    
    jynetwork::proto::SCMessageLoginAuth* GetSCMessageLoginAuth() { return _msg_login_auth.get(); }
    
    void handle_connect(const boost::system::error_code& ec,
                        boost::asio::ip::tcp::resolver::iterator endpoint_iter);
    
    static BaseSocket* m_pInstance;
    
    std::unique_ptr<boost::asio::ip::tcp::socket> _socket;

    
    std::unique_ptr<boost::asio::io_service::work> _io_work;
    
    std::vector<std::thread> _io_threads;
    
//    chat_message read_msg_;
//    chat_message_queue write_msgs_;
    
    std::atomic<bool> _is_connecting;
    std::atomic<bool> _is_connected;
    std::atomic<bool> _is_reconnect;
    std::atomic<bool> _is_auto_connect;
    bool _is_need_full_data;
    int _try_connect_game_server;
    bool _is_allow_ping = false;
    std::atomic<bool> _stopped;
    bool _is_writing;
    
    uint16_t _ack_opcode;
    uint16_t _ack_opcode_bak;
    uint16_t _ack_operation;
    uint16_t _ack_operation_bak;
    
    std::unique_ptr<jynetwork::proto::SCMessageLoginAuth> _msg_login_auth;
    std::atomic<bool> _is_start;
    std::atomic<bool> _is_gateway_change;
    int _gateway_step;
    std::string _server_address;
    uint32_t _server_port;
    
    BaseMessage _write_msg;
    BaseMessage _read_msg;
    
    std::list<SocketMessageCell> _message_list;
    std::function<bool(BaseSocket*, uint16_t, std::shared_ptr<::google::protobuf::MessageLite>)> _func_handle_message;


    
};

#endif /* BaseSocket_h */
