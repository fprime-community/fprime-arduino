// ======================================================================
// \title  TcpClient.hpp
// \author ethanchee
// \brief  hpp file for TcpClient component implementation class
// ======================================================================

#ifndef TcpClient_HPP
#define TcpClient_HPP

#include <Drv/Ip/IpSocket.hpp>
#include <IpCfg.hpp>
#include "Arduino/Drv/TcpClient/TcpClientComponentAc.hpp"
#include <WiFi.h>

namespace Arduino {

  class TcpClient :
    public TcpClientComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object TcpClient
      //!
      TcpClient(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object TcpClient
      //!
      ~TcpClient();

      Drv::SocketIpStatus setupWiFi(char* ssid, const char* password);

      Drv::SocketIpStatus configure(const char* hostname,
                               const U16 port,
                               const U32 send_timeout_seconds = SOCKET_SEND_TIMEOUT_SECONDS,
                               const U32 send_timeout_microseconds = SOCKET_SEND_TIMEOUT_MICROSECONDS);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< 
      The call order
      */
      );

      //! Handler implementation for send
      //!
      Drv::SendStatus send_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &sendBuffer 
      );

      WiFiClient client;
      bool client_connected;

    };

} // end namespace Arduino

#endif
