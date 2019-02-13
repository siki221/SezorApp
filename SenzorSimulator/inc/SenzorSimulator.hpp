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
 * File:   SenzorSimulator.hpp
 * Author: Matus Bodorik
 */


#include "IPCInterface.h"
#include "GenericClient.h"

namespace flexd{
    namespace senzors {
        class SenzorSimulator : public flexd::gen::IPCInterface{
        public:
            SenzorSimulator(flexd::icl::ipc::FleXdEpoll& poller);
            ~SenzorSimulator() override;
            SenzorSimulator(const SenzorSimulator&) = delete;

            virtual void onConnectPeer(uint32_t peerID, bool genericPeer) override;
            void onTimer() override;

            double generateValue(int from, int to);
            uint64_t getTimestamp();

        private:
            uint16_t m_periodTime;
            flexd::icl::ipc::FleXdTimer m_SenzorTimer;
            int m_previosTemperature;
            int m_previosHumidity;
            int m_previosPreasure;
        };
    }
}
