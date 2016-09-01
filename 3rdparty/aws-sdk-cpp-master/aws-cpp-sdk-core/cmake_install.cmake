# Install script for directory: /home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaws-cpp-sdk-core.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaws-cpp-sdk-core.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaws-cpp-sdk-core.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/libaws-cpp-sdk-core.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaws-cpp-sdk-core.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaws-cpp-sdk-core.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libaws-cpp-sdk-core.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/SDKConfig.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/AmazonWebServiceRequest.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/Core_EXPORTS.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/AmazonWebServiceResult.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/Version.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/AmazonStreamingWebServiceRequest.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/NoResult.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/Aws.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/AmazonSerializableWebServiceRequest.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/Globals.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/VersionConfig.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/Region.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/auth" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/auth/AWSCredentialsProviderChain.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/auth/AWSCredentialsProvider.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/auth/AWSAuthSigner.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/client" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/client/CoreErrors.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/client/AsyncCallerContext.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/client/RetryStrategy.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/client/AWSErrorMarshaller.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/client/AWSError.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/client/DefaultRetryStrategy.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/client/ClientConfiguration.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/client/AWSClient.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/internal" TYPE FILE FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/internal/EC2MetadataClient.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/http" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/HttpRequest.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/HttpTypes.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/URI.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/HttpResponse.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/HttpClient.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/Scheme.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/HttpClientFactory.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/http/standard" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/standard/StandardHttpRequest.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/standard/StandardHttpResponse.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/platform" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/platform/Security.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/platform/Platform.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/platform/OSVersionInfo.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/platform/Time.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/platform/Android.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/platform/FileSystem.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/platform/Environment.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/GetTheLights.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/StringUtils.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/EnumParseOverflowContainer.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/FileSystemUtils.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/Array.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/UUID.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/UnreferencedParam.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/HashingUtils.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/DateTime.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/Outcome.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/base64" TYPE FILE FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/base64/Base64.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/crypto" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/MD5.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/CryptoBuf.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/Sha256HMAC.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/Sha256.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/HashResult.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/HMAC.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/Hash.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/CryptoStream.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/Factories.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/Cipher.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/SecureRandom.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/json" TYPE FILE FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/json/JsonSerializer.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/xml" TYPE FILE FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/xml/XmlSerializer.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/logging" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/logging/LogSystemInterface.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/logging/AWSLogging.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/logging/LogLevel.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/logging/FormattedLogSystem.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/logging/DefaultLogSystem.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/logging/LogMacros.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/logging/ConsoleLogSystem.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/logging/NullLogSystem.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/memory" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/AWSMemory.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/MemorySystemInterface.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/memory/stl" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSString.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSStreamFwd.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSStringStream.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSDeque.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSMultiMap.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSStack.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSMap.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSAllocator.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSVector.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSList.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSQueue.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSSet.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/memory/stl/AWSFunction.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/ratelimiter" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/ratelimiter/RateLimiterInterface.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/ratelimiter/DefaultRateLimiter.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/stream" TYPE FILE FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/stream/ResponseStream.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/threading" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/threading/ThreadTask.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/threading/Executor.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/external/json-cpp" TYPE FILE FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/external/json-cpp/json.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/external/tinyxml2" TYPE FILE FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/external/tinyxml2/tinyxml2.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/http/curl" TYPE FILE FILES
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/curl/CurlHttpClient.h"
    "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/http/curl/CurlHandleContainer.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aws/core/utils/crypto/openssl" TYPE FILE FILES "/home/prateeks/code/aws-sdk-cpp-master/aws-cpp-sdk-core/include/aws/core/utils/crypto/openssl/CryptoImpl.h")
endif()

