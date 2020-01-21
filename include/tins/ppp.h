/*
 * Copyright (c) 2017, Matias Fontanini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef TINS_PPP_H
#define TINS_PPP_H

#include <string>
#include <vector>
#include <tins/pdu.h>
#include <tins/macros.h>
#include <tins/endianness.h>
#include <tins/small_uint.h>
#include <tins/pdu_option.h>
#include <tins/cxxstd.h>

namespace Tins {
/**
 * \class PPP
 * \brief Represents a Point-to-point protocol over Ethernet PDU.
 */
class TINS_API PPP : public PDU {
public:
    /**
     * This PDU's flag.
     */
    static const PDU::PDUType pdu_flag = PDU::PPP;

    /**
     * \brief Default constructor.
     * 
     * This sets the version and type fields to 0x1.
     */
    PPP();
    
    /**
     * \brief Constructor which creates an PPP object from a buffer.
     * 
     * If there is not enough size for a PPP header, a malformed_packet
     * exception is thrown.
     * 
     * \param buffer The buffer from which this PDU will be constructed.
     * \param total_sz The total size of the buffer.
     */
    PPP(const uint8_t* buffer, uint32_t total_sz);

    // Getters

    /**
     *  \brief Getter for the payload_length field.
     *  \return The stored payload_length field value.
     */
    uint16_t protocol() const {
        return Endian::be_to_host(header_.protocol);
    }
    
    /**
     * \brief Returns the header size.
     *
     * This method overrides PDU::header_size. \sa PDU::header_size
     */
    uint32_t header_size() const override;

    /**
     * \sa PDU::clone
     */
    PPP* clone() const override {
        return new PPP(*this);
    }

    /**
     * \brief Getter for the PDU's type.
     * \sa PDU::pdu_type
     */
    PDUType pdu_type() const override {
        return pdu_flag;
    }

    // Setters

    void protocol(uint16_t new_protocol);
private:
    void write_serialization(uint8_t* buffer, uint32_t total_sz) override;

    TINS_BEGIN_PACK
    struct ppp_header {
        uint16_t protocol;
    } TINS_END_PACK;

    ppp_header header_;
};
}

#endif // TINS_PPP_H
