/*
 * Copyright (c) 2015 - 2025, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NRF_SPI_H__
#define NRF_SPI_H__

#include <nrfx.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_spi_hal SPI HAL
 * @{
 * @ingroup nrf_spi
 * @brief   Hardware access layer for managing the SPI peripheral.
 */

/**
 * @brief Macro getting pointer to the structure of registers of the SPI peripheral.
 *
 * @param[in] idx SPI instance index.
 *
 * @return Pointer to the structure of registers of the SPI peripheral.
 */
#define NRF_SPI_INST_GET(idx) NRFX_CONCAT(NRF_, SPI, idx)

/**
 * @brief This value can be used as a parameter for the @ref nrf_spi_pins_set
 *        function to specify that a given SPI signal (SCK, MOSI, or MISO)
 *        shall not be connected to a physical pin.
 */
#define NRF_SPI_PIN_NOT_CONNECTED  0xFFFFFFFF


/** @brief SPI events. */
typedef enum
{
    NRF_SPI_EVENT_READY = offsetof(NRF_SPI_Type, EVENTS_READY) ///< TXD byte sent and RXD byte received.
} nrf_spi_event_t;

/** @brief SPI interrupts. */
typedef enum
{
    NRF_SPI_INT_READY_MASK = SPI_INTENSET_READY_Msk, ///< Interrupt on READY event.
    NRF_SPI_ALL_INTS_MASK  = SPI_INTENSET_READY_Msk  ///< All SPI interrupts.
} nrf_spi_int_mask_t;

/** @brief SPI data rates. */
typedef enum
{
    NRF_SPI_FREQ_125K = SPI_FREQUENCY_FREQUENCY_K125,   ///< 125 kbps.
    NRF_SPI_FREQ_250K = SPI_FREQUENCY_FREQUENCY_K250,   ///< 250 kbps.
    NRF_SPI_FREQ_500K = SPI_FREQUENCY_FREQUENCY_K500,   ///< 500 kbps.
    NRF_SPI_FREQ_1M   = SPI_FREQUENCY_FREQUENCY_M1,     ///< 1 Mbps.
    NRF_SPI_FREQ_2M   = SPI_FREQUENCY_FREQUENCY_M2,     ///< 2 Mbps.
    NRF_SPI_FREQ_4M   = SPI_FREQUENCY_FREQUENCY_M4,     ///< 4 Mbps.
    // [conversion to 'int' needed to prevent compilers from complaining
    //  that the provided value (0x80000000UL) is out of range of "int"]
    NRF_SPI_FREQ_8M   = (int)SPI_FREQUENCY_FREQUENCY_M8 ///< 8 Mbps.
} nrf_spi_frequency_t;

/** @brief SPI modes. */
typedef enum
{
    NRF_SPI_MODE_0, ///< SCK active high, sample on leading edge of clock.
    NRF_SPI_MODE_1, ///< SCK active high, sample on trailing edge of clock.
    NRF_SPI_MODE_2, ///< SCK active low, sample on leading edge of clock.
    NRF_SPI_MODE_3  ///< SCK active low, sample on trailing edge of clock.
} nrf_spi_mode_t;

/** @brief SPI bit orders. */
typedef enum
{
    NRF_SPI_BIT_ORDER_MSB_FIRST = SPI_CONFIG_ORDER_MsbFirst, ///< Most significant bit shifted out first.
    NRF_SPI_BIT_ORDER_LSB_FIRST = SPI_CONFIG_ORDER_LsbFirst  ///< Least significant bit shifted out first.
} nrf_spi_bit_order_t;


/**
 * @brief Function for clearing the specified SPI event.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] event Event to be cleared.
 */
NRF_STATIC_INLINE void nrf_spi_event_clear(NRF_SPI_Type *  p_reg,
                                           nrf_spi_event_t event);

/**
 * @brief Function for retrieving the state of the SPI event.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] event Event to be checked.
 *
 * @retval true  The event has been generated.
 * @retval false The event has not been generated.
 */
NRF_STATIC_INLINE bool nrf_spi_event_check(NRF_SPI_Type const * p_reg,
                                           nrf_spi_event_t      event);

/**
 * @brief Function for getting the address of the specified SPI event register.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] event The specified event.
 *
 * @return Address of the specified event register.
 */
NRF_STATIC_INLINE uint32_t nrf_spi_event_address_get(NRF_SPI_Type const * p_reg,
                                                     nrf_spi_event_t      event);

/**
 * @brief Function for enabling the specified interrupts.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Mask of interrupts to be enabled.
 *                  Use @ref nrf_spi_int_mask_t values for bit masking.
 */
NRF_STATIC_INLINE void nrf_spi_int_enable(NRF_SPI_Type * p_reg,
                                          uint32_t       mask);

/**
 * @brief Function for disabling the specified interrupts.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Mask of interrupts to be disabled.
 *                  Use @ref nrf_spi_int_mask_t values for bit masking.
 */
NRF_STATIC_INLINE void nrf_spi_int_disable(NRF_SPI_Type * p_reg,
                                           uint32_t       mask);

/**
 * @brief Function for checking if the specified interrupts are enabled.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Mask of interrupts to be checked.
 *                  Use @ref nrf_spi_int_mask_t values for bit masking.
 *
 * @return Mask of enabled interrupts.
 */
NRF_STATIC_INLINE uint32_t nrf_spi_int_enable_check(NRF_SPI_Type const * p_reg, uint32_t mask);

/**
 * @brief Function for enabling the SPI peripheral.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 */
NRF_STATIC_INLINE void nrf_spi_enable(NRF_SPI_Type * p_reg);

/**
 * @brief Function for disabling the SPI peripheral.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 */
NRF_STATIC_INLINE void nrf_spi_disable(NRF_SPI_Type * p_reg);

/**
 * @brief Function for configuring SPI pins.
 *
 * If a given signal is not needed, pass the @ref NRF_SPI_PIN_NOT_CONNECTED
 * value instead of its pin number.
 *
 * @param[in] p_reg    Pointer to the structure of registers of the peripheral.
 * @param[in] sck_pin  SCK pin number.
 * @param[in] mosi_pin MOSI pin number.
 * @param[in] miso_pin MISO pin number.
 */
NRF_STATIC_INLINE void nrf_spi_pins_set(NRF_SPI_Type * p_reg,
                                        uint32_t       sck_pin,
                                        uint32_t       mosi_pin,
                                        uint32_t       miso_pin);

/**
 * @brief Function for setting the SCK pin.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] pin   SCK pin number.
 */
NRF_STATIC_INLINE void nrf_spi_sck_pin_set(NRF_SPI_Type * p_reg, uint32_t pin);

/**
 * @brief Function for setting the MOSI pin
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] pin   MOSI pin number.
 */
NRF_STATIC_INLINE void nrf_spi_mosi_pin_set(NRF_SPI_Type * p_reg, uint32_t pin);

/**
 * @brief Function for setting the MISO pin.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] pin   MISO pin number.
 */
NRF_STATIC_INLINE void nrf_spi_miso_pin_set(NRF_SPI_Type * p_reg, uint32_t pin);

/**
 * @brief Function for getting the SCK pin selection.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @return SCK pin selection;
 */
NRF_STATIC_INLINE uint32_t nrf_spi_sck_pin_get(NRF_SPI_Type const * p_reg);

/**
 * @brief Function for getting the MOSI pin selection.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @return MOSI pin selection;
 */
NRF_STATIC_INLINE uint32_t nrf_spi_mosi_pin_get(NRF_SPI_Type const * p_reg);

/**
 * @brief Function for getting the MISO pin selection.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @return MISO pin selection;
 */
NRF_STATIC_INLINE uint32_t nrf_spi_miso_pin_get(NRF_SPI_Type const * p_reg);

/**
 * @brief Function for writing data to the SPI transmitter register.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] data  TX data to send.
 */
NRF_STATIC_INLINE void nrf_spi_txd_set(NRF_SPI_Type * p_reg, uint8_t data);

/**
 * @brief Function for reading data from the SPI receiver register.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @return RX data received.
 */
NRF_STATIC_INLINE uint8_t nrf_spi_rxd_get(NRF_SPI_Type const * p_reg);

/**
 * @brief Function for setting the SPI master data rate.
 *
 * @param[in] p_reg     Pointer to the structure of registers of the peripheral.
 * @param[in] frequency SPI frequency.
 */
NRF_STATIC_INLINE void nrf_spi_frequency_set(NRF_SPI_Type *      p_reg,
                                             nrf_spi_frequency_t frequency);

/**
 * @brief Function for setting the SPI configuration.
 *
 * @param[in] p_reg         Pointer to the structure of registers of the peripheral.
 * @param[in] spi_mode      SPI mode.
 * @param[in] spi_bit_order SPI bit order.
 */
NRF_STATIC_INLINE void nrf_spi_configure(NRF_SPI_Type *      p_reg,
                                         nrf_spi_mode_t      spi_mode,
                                         nrf_spi_bit_order_t spi_bit_order);


#ifndef NRF_DECLARE_ONLY

NRF_STATIC_INLINE void nrf_spi_event_clear(NRF_SPI_Type *  p_reg,
                                           nrf_spi_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
    nrf_event_readback((uint8_t *)p_reg + (uint32_t)event);
}

NRF_STATIC_INLINE bool nrf_spi_event_check(NRF_SPI_Type const * p_reg,
                                           nrf_spi_event_t      event)
{
    return nrf_event_check(p_reg, event);
}

NRF_STATIC_INLINE uint32_t nrf_spi_event_address_get(NRF_SPI_Type const * p_reg,
                                                     nrf_spi_event_t      event)
{
    return nrf_task_event_address_get(p_reg, event);
}

NRF_STATIC_INLINE void nrf_spi_int_enable(NRF_SPI_Type * p_reg,
                                          uint32_t       mask)
{
    p_reg->INTENSET = mask;
}

NRF_STATIC_INLINE void nrf_spi_int_disable(NRF_SPI_Type * p_reg,
                                           uint32_t       mask)
{
    p_reg->INTENCLR = mask;
}

NRF_STATIC_INLINE uint32_t nrf_spi_int_enable_check(NRF_SPI_Type const * p_reg, uint32_t mask)
{
    return p_reg->INTENSET & mask;
}

NRF_STATIC_INLINE void nrf_spi_enable(NRF_SPI_Type * p_reg)
{
    p_reg->ENABLE = (SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos);
}

NRF_STATIC_INLINE void nrf_spi_disable(NRF_SPI_Type * p_reg)
{
    p_reg->ENABLE = (SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos);
}

NRF_STATIC_INLINE void nrf_spi_pins_set(NRF_SPI_Type * p_reg,
                                        uint32_t       sck_pin,
                                        uint32_t       mosi_pin,
                                        uint32_t       miso_pin)
{
#if defined(SPI_PSEL_SCK_CONNECT_Pos)
    p_reg->PSEL.SCK = sck_pin;
#else
    p_reg->PSELSCK  = sck_pin;
#endif

#if defined(SPI_PSEL_MOSI_CONNECT_Pos)
    p_reg->PSEL.MOSI = mosi_pin;
#else
    p_reg->PSELMOSI = mosi_pin;
#endif

#if defined(SPI_PSEL_MISO_CONNECT_Pos)
    p_reg->PSEL.MISO = miso_pin;
#else
    p_reg->PSELMISO = miso_pin;
#endif
}

NRF_STATIC_INLINE void nrf_spi_sck_pin_set(NRF_SPI_Type * p_reg, uint32_t pin)
{
#if defined(SPI_PSEL_SCK_CONNECT_Pos)
    p_reg->PSEL.SCK = pin;
#else
    p_reg->PSELSCK  = pin;
#endif
}

NRF_STATIC_INLINE void nrf_spi_mosi_pin_set(NRF_SPI_Type * p_reg, uint32_t pin)
{
#if defined(SPI_PSEL_MOSI_CONNECT_Pos)
    p_reg->PSEL.MOSI = pin;
#else
    p_reg->PSELMOSI = pin;
#endif
}

NRF_STATIC_INLINE void nrf_spi_miso_pin_set(NRF_SPI_Type * p_reg, uint32_t pin)
{
#if defined(SPI_PSEL_MISO_CONNECT_Pos)
    p_reg->PSEL.MISO = pin;
#else
    p_reg->PSELMISO = pin;
#endif
}

NRF_STATIC_INLINE uint32_t nrf_spi_sck_pin_get(NRF_SPI_Type const * p_reg)
{
#if defined(SPI_PSEL_SCK_CONNECT_Pos)
    return p_reg->PSEL.SCK;
#else
    return p_reg->PSELSCK;
#endif
}

NRF_STATIC_INLINE uint32_t nrf_spi_mosi_pin_get(NRF_SPI_Type const * p_reg)
{
#if defined(SPI_PSEL_MOSI_CONNECT_Pos)
    return p_reg->PSEL.MOSI;
#else
    return p_reg->PSELMOSI;
#endif
}

NRF_STATIC_INLINE uint32_t nrf_spi_miso_pin_get(NRF_SPI_Type const * p_reg)
{
#if defined(SPI_PSEL_MISO_CONNECT_Pos)
    return p_reg->PSEL.MISO;
#else
    return p_reg->PSELMISO;
#endif
}

NRF_STATIC_INLINE void nrf_spi_txd_set(NRF_SPI_Type * p_reg, uint8_t data)
{
    p_reg->TXD = data;
}

NRF_STATIC_INLINE uint8_t nrf_spi_rxd_get(NRF_SPI_Type const * p_reg)
{
    return (uint8_t)p_reg->RXD;
}

NRF_STATIC_INLINE void nrf_spi_frequency_set(NRF_SPI_Type *      p_reg,
                                             nrf_spi_frequency_t frequency)
{
    p_reg->FREQUENCY = (uint32_t)frequency;
}

NRF_STATIC_INLINE void nrf_spi_configure(NRF_SPI_Type *      p_reg,
                                         nrf_spi_mode_t      spi_mode,
                                         nrf_spi_bit_order_t spi_bit_order)
{
    uint32_t config = (spi_bit_order == NRF_SPI_BIT_ORDER_MSB_FIRST ?
        SPI_CONFIG_ORDER_MsbFirst : SPI_CONFIG_ORDER_LsbFirst);
    switch (spi_mode)
    {
    default:
    case NRF_SPI_MODE_0:
        config |= (SPI_CONFIG_CPOL_ActiveHigh << SPI_CONFIG_CPOL_Pos) |
                  (SPI_CONFIG_CPHA_Leading    << SPI_CONFIG_CPHA_Pos);
        break;

    case NRF_SPI_MODE_1:
        config |= (SPI_CONFIG_CPOL_ActiveHigh << SPI_CONFIG_CPOL_Pos) |
                  (SPI_CONFIG_CPHA_Trailing   << SPI_CONFIG_CPHA_Pos);
        break;

    case NRF_SPI_MODE_2:
        config |= (SPI_CONFIG_CPOL_ActiveLow  << SPI_CONFIG_CPOL_Pos) |
                  (SPI_CONFIG_CPHA_Leading    << SPI_CONFIG_CPHA_Pos);
        break;

    case NRF_SPI_MODE_3:
        config |= (SPI_CONFIG_CPOL_ActiveLow  << SPI_CONFIG_CPOL_Pos) |
                  (SPI_CONFIG_CPHA_Trailing   << SPI_CONFIG_CPHA_Pos);
        break;
    }
    p_reg->CONFIG = config;
}

#endif // NRF_DECLARE_ONLY

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_SPI_H__
