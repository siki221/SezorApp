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
 * File:   main.cpp
 * Author: Matus Bodorik
 */

#include "FleXdEpoll.h"
#include "SenzorSimulator.hpp"
#include "FleXdEvent.h"
#include "FleXdLogger.h"

int main(int argc, char** argv) {

    flexd::icl::ipc::FleXdEpoll poller(10);
    flexd::icl::ipc::FleXdTermEvent e(poller);

    if(e.init()){
        FLEX_LOG_INIT( poller, "SenzorSimulator");
        FLEX_LOG_INFO("SenzorSimulator -> Start");
        flexd::senzors::SenzorSimulator senzorSimulator(poller);
        if(senzorSimulator.initGenericServer()){
            poller.loop();
        }
        FLEX_LOG_UNINIT();
    }

    return 0;
}
