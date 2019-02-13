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
 * File:   SenzorReader.cpp
 * Author: Matus Bodorik
 */

#include "SenzorReader.hpp"
#include "IPCInterface.h"
#include "GenericClient.h"
#include "FleXdEpoll.h"
#include "FleXdTimer.h"
#include "FleXdLogger.h"
#include "JsonObj.h"


namespace flexd{
    namespace senzors {

                SenzorReader::SenzorReader(flexd::icl::ipc::FleXdEpoll& poller)
                :IPCInterface(11111, poller),
                m_periodTime(1),
                m_SenzorTimer(poller, m_periodTime, 0, true, [this](void){ this->onTimer(); }),
                m_previosTemperature(20),
                m_previosHumidity(50),
                m_previosPreasure(400)
                {
                    if(m_SenzorTimer.start())
                    {
                      FLEX_LOG_INFO("SenzorSimulator::SenzorSimulator -> FleXdTimer.start() successful");
                    } else {
                        FLEX_LOG_INFO("SenzorSimulator::SenzorSimulator -> FleXdTimer.start() failed");
                    }
                }

                SenzorReader::~SenzorReader(){
                    m_SenzorTimer.stop();
                }

                void SenzorReader::onConnectPeer(uint32_t peerID, bool genericPeer) {}

                void SenzorReader::onTimer(){
                    double temperature;
                    temperature = m_previosTemperature = generateValue(m_previosTemperature - 2, m_previosTemperature + 2);
                    if(m_previosTemperature > 40 || m_previosTemperature < -25) m_previosTemperature = 20;
                    FLEX_LOG_INFO("Temperature: ", temperature , "°C");

                    double preasure;
                    preasure = m_previosPreasure = generateValue(m_previosPreasure - 50 , m_previosPreasure + 50);
                    if(m_previosPreasure > 1000 || m_previosPreasure < 100) m_previosPreasure = 500;
                    FLEX_LOG_INFO("preasure: ", preasure , "Hpa");

                    double humidity;
                    humidity = m_previosHumidity = generateValue(m_previosHumidity - 5, m_previosHumidity + 5);
                    if(m_previosHumidity > 90 || m_previosHumidity < 10) m_previosHumidity = 50;
                    FLEX_LOG_INFO("humidity: ", humidity , "%");

                    flexd::icl::JsonObj json;
                    json.add<std::string>("/Location", "ROOM0");
                    json.add<double>("/Temperature", temperature);
                    json.add<double>("/Humidity", humidity);
                    json.add<double>("/Preasure", preasure);
                    json.add<uint64_t>("/Timestamp", getTimestamp());

                    std::shared_ptr<GenericClient::Header> header = std::make_shared<GenericClient::Header>();
                    header->from = 11111;
                    header->to = 12345;
                    sendSenzorData(header, 11111, json.getJson());
                }

                double SenzorReader::generateValue(int from, int to)
                {
                    srand(time(NULL));
                    return rand() % (to - from + 1) + from;
                }

                uint64_t SenzorReader::getTimestamp() {
                    std::chrono::time_point<std::chrono::system_clock> p;
                    p = std::chrono::system_clock::now();
                    std::time_t time = std::chrono::duration_cast<std::chrono::milliseconds>(p.time_since_epoch()).count();
                    return static_cast<uint64_t> (time);
                }

    } //namespace senzors
} //namespace flexd
