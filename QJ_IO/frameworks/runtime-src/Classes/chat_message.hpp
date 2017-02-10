//
//  chat_message.hpp
//  ChatClient
//
//  Created by HongAndy on 16/4/4.
//  Copyright © 2016年 HongAndy. All rights reserved.
//

//
// chat_message.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:
    enum { header_length = 4 };
    enum { op_length = 2};
    enum { max_body_length = 512 };
    
    chat_message()
    : body_length_(0)
    {
    }
    
    const char* data() const
    {
        return data_;
    }
    
    char* data()
    {
        return data_;
    }
    
    std::size_t length() const
    {
        return header_length + body_length_;
    }
    
    const char* body() const
    {
        return data_ + header_length;
    }
    
    char* body()
    {
        return data_ + header_length;
    }
    
    const char* bodyContent() const
    {
        return data_ + header_length+op_length;
    }
    
    char* bodyContent()
    {
        return data_ + header_length+op_length;
    }
    
    //    const char* opCode() const
    //    {
    //        return data_ + header_length;
    //    }
    //
    //
    //    char* opCode()
    //    {
    //        return data_ + header_length;
    //    }
    
    std::size_t bodyContent_length() const
    {
        return body_length_-op_length;
    }
    
    
    
    std::size_t body_length() const
    {
        return body_length_;
    }
    
    std::size_t opCode_length() const
    {
        return op_length;
    }
    
    
    void body_length(std::size_t new_length)
    {
        body_length_ = new_length;
        if (body_length_ > max_body_length)
            body_length_ = max_body_length;
    }
    
    int16_t opCode(){
        return opcode;
    }
    
    bool decode_op()
    {
        char op[op_length + 1] = "";
        std::strncat(op, data_+header_length, op_length);
        opcode = std::atoi(op);
        
        if(opcode>0)
            return true;
        return false;
    }
    
    void encode_op()
    {
        char op[op_length + 1] = "";
        std::sprintf(op, "%2d",opcode);
        std::memcpy(data_+header_length, op, op_length);
    }
    
    void setOpcode(int16_t _opCode){
        opcode = _opCode;
    }
    
    
    bool decode_header()
    {
        char header[header_length + 1] = "";
        std::strncat(header, data_, header_length);
        body_length_ = std::atoi(header);
        if (body_length_ > max_body_length)
        {
            body_length_ = 0;
            return false;
        }
        return true;
    }
    
    void encode_header()
    {
        char header[header_length + 1] = "";
        std::sprintf(header, "%4d", static_cast<int>(body_length_));
        std::memcpy(data_, header, header_length);
    }
    
private:
    char data_[header_length + max_body_length];
    std::size_t body_length_;
    int16_t opcode;
};

#endif // CHAT_MESSAGE_HPP
