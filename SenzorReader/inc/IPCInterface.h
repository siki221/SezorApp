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
#ifndef IPCINTERFACE_H
#define IPCINTERFACE_H

#include <FleXdEpoll.h>
#include <FleXdIPCMsg.h>
#include <FleXdIPCConnector.h>
#include "GenericClient.h"
#include "JsonObj.h"
#include <memory>
#include <cstdint>

namespace flexd{
    namespace gen{

        class IPCInterface : public flexd::icl::ipc::IPCConnector, public flexd::gen::GenericClient {
        public:
            IPCInterface(uint32_t ipdID, flexd::icl::ipc::FleXdEpoll& poller);
            virtual ~IPCInterface() = default;

            virtual void onTimer() = 0;
            virtual void onConnectPeer(uint32_t peerID, bool genericPeer) = 0;
            void sendSenzorData(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& PayloadMsg);
        private:
            void send ( std::shared_ptr<flexd::icl::ipc::FleXdIPCMsg> msg, uint32_t peerID );
            void receiveMsg(flexd::icl::ipc::pSharedFleXdIPCMsg msg);
        };

    } //namespace bus
} //namespace flexd

#endif // IPCINTERFACE_H 
