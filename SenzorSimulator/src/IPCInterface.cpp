/*
 * Copyright (c) 2018, Globallogic s.r.o.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *  * Neither the name of the Globallogic s.r.o. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC S.R.O. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * File:   IPCInterface.cpp
 * Author: Matus Bodorik
 */

#include "IPCInterface.h"
#include <FleXdIPCMsgTypes.h>
#include <JsonObj.h>
#include <ctime>
#include <chrono>
 
namespace flexd {
  namespace gen {

        IPCInterface::IPCInterface (uint32_t ipdID, flexd::icl::ipc::FleXdEpoll& poller)
        :IPCConnector(ipdID, poller, true), GenericClient()
        {

          addPeer(12345);
        }

        void IPCInterface::sendSenzorData(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& PayloadMsg)
        {

           int id = 6;

           flexd::icl::JsonObj json = {};

           json.add<int>("/id", id);
           json.add<uint32_t>("/payload/ID", ID);
           json.add<std::string>("/payload/PayloadMsg", PayloadMsg);
           send(msgWrap(header, json.getJson()), header->to);
        }


        void IPCInterface::send(std::shared_ptr<flexd::icl::ipc::FleXdIPCMsg> Msg, uint32_t peerID) {
            if(sendMsg(Msg, peerID)) {
                m_counter++;
            }
        }

        void IPCInterface::receiveMsg(flexd::icl::ipc::pSharedFleXdIPCMsg msg)
        {
        }
    } //namespace bus
} //namespace flexd

