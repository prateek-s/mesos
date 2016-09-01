/*
* Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/
#include <aws/core/utils/Outcome.h>
#include <aws/core/auth/AWSAuthSigner.h>
#include <aws/core/client/CoreErrors.h>
#include <aws/core/client/RetryStrategy.h>
#include <aws/core/http/HttpClient.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/core/http/HttpClientFactory.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>
#include <aws/core/utils/threading/Executor.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/CognitoIdentityProviderEndpoint.h>
#include <aws/cognito-idp/CognitoIdentityProviderErrorMarshaller.h>
#include <aws/cognito-idp/model/AddCustomAttributesRequest.h>
#include <aws/cognito-idp/model/AdminConfirmSignUpRequest.h>
#include <aws/cognito-idp/model/AdminDeleteUserRequest.h>
#include <aws/cognito-idp/model/AdminDeleteUserAttributesRequest.h>
#include <aws/cognito-idp/model/AdminDisableUserRequest.h>
#include <aws/cognito-idp/model/AdminEnableUserRequest.h>
#include <aws/cognito-idp/model/AdminForgetDeviceRequest.h>
#include <aws/cognito-idp/model/AdminGetDeviceRequest.h>
#include <aws/cognito-idp/model/AdminGetUserRequest.h>
#include <aws/cognito-idp/model/AdminInitiateAuthRequest.h>
#include <aws/cognito-idp/model/AdminListDevicesRequest.h>
#include <aws/cognito-idp/model/AdminResetUserPasswordRequest.h>
#include <aws/cognito-idp/model/AdminRespondToAuthChallengeRequest.h>
#include <aws/cognito-idp/model/AdminSetUserSettingsRequest.h>
#include <aws/cognito-idp/model/AdminUpdateDeviceStatusRequest.h>
#include <aws/cognito-idp/model/AdminUpdateUserAttributesRequest.h>
#include <aws/cognito-idp/model/AdminUserGlobalSignOutRequest.h>
#include <aws/cognito-idp/model/ChangePasswordRequest.h>
#include <aws/cognito-idp/model/ConfirmDeviceRequest.h>
#include <aws/cognito-idp/model/ConfirmForgotPasswordRequest.h>
#include <aws/cognito-idp/model/ConfirmSignUpRequest.h>
#include <aws/cognito-idp/model/CreateUserPoolRequest.h>
#include <aws/cognito-idp/model/CreateUserPoolClientRequest.h>
#include <aws/cognito-idp/model/DeleteUserRequest.h>
#include <aws/cognito-idp/model/DeleteUserAttributesRequest.h>
#include <aws/cognito-idp/model/DeleteUserPoolRequest.h>
#include <aws/cognito-idp/model/DeleteUserPoolClientRequest.h>
#include <aws/cognito-idp/model/DescribeUserPoolRequest.h>
#include <aws/cognito-idp/model/DescribeUserPoolClientRequest.h>
#include <aws/cognito-idp/model/ForgetDeviceRequest.h>
#include <aws/cognito-idp/model/ForgotPasswordRequest.h>
#include <aws/cognito-idp/model/GetDeviceRequest.h>
#include <aws/cognito-idp/model/GetUserRequest.h>
#include <aws/cognito-idp/model/GetUserAttributeVerificationCodeRequest.h>
#include <aws/cognito-idp/model/GlobalSignOutRequest.h>
#include <aws/cognito-idp/model/InitiateAuthRequest.h>
#include <aws/cognito-idp/model/ListDevicesRequest.h>
#include <aws/cognito-idp/model/ListUserPoolClientsRequest.h>
#include <aws/cognito-idp/model/ListUserPoolsRequest.h>
#include <aws/cognito-idp/model/ListUsersRequest.h>
#include <aws/cognito-idp/model/ResendConfirmationCodeRequest.h>
#include <aws/cognito-idp/model/RespondToAuthChallengeRequest.h>
#include <aws/cognito-idp/model/SetUserSettingsRequest.h>
#include <aws/cognito-idp/model/SignUpRequest.h>
#include <aws/cognito-idp/model/UpdateDeviceStatusRequest.h>
#include <aws/cognito-idp/model/UpdateUserAttributesRequest.h>
#include <aws/cognito-idp/model/UpdateUserPoolRequest.h>
#include <aws/cognito-idp/model/UpdateUserPoolClientRequest.h>
#include <aws/cognito-idp/model/VerifyUserAttributeRequest.h>

using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace Aws::CognitoIdentityProvider;
using namespace Aws::CognitoIdentityProvider::Model;
using namespace Aws::Http;
using namespace Aws::Utils::Json;

static const char* SERVICE_NAME = "cognito-idp";
static const char* ALLOCATION_TAG = "CognitoIdentityProviderClient";


CognitoIdentityProviderClient::CognitoIdentityProviderClient(const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, Aws::MakeShared<DefaultAWSCredentialsProviderChain>(ALLOCATION_TAG),
        SERVICE_NAME, clientConfiguration.authenticationRegion.empty() ? RegionMapper::GetRegionName(clientConfiguration.region)
                                                                        : clientConfiguration.authenticationRegion),
    Aws::MakeShared<CognitoIdentityProviderErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

CognitoIdentityProviderClient::CognitoIdentityProviderClient(const AWSCredentials& credentials, const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, Aws::MakeShared<SimpleAWSCredentialsProvider>(ALLOCATION_TAG, credentials),
         SERVICE_NAME, clientConfiguration.authenticationRegion.empty() ? RegionMapper::GetRegionName(clientConfiguration.region)
                                                                        : clientConfiguration.authenticationRegion),
    Aws::MakeShared<CognitoIdentityProviderErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

CognitoIdentityProviderClient::CognitoIdentityProviderClient(const std::shared_ptr<AWSCredentialsProvider>& credentialsProvider,
  const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, credentialsProvider,
         SERVICE_NAME, clientConfiguration.authenticationRegion.empty() ? RegionMapper::GetRegionName(clientConfiguration.region)
                                                                        : clientConfiguration.authenticationRegion),
    Aws::MakeShared<CognitoIdentityProviderErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

CognitoIdentityProviderClient::~CognitoIdentityProviderClient()
{
}

void CognitoIdentityProviderClient::init(const ClientConfiguration& config)
{
  Aws::StringStream ss;
  ss << SchemeMapper::ToString(config.scheme) << "://";

  if(config.endpointOverride.empty() && config.authenticationRegion.empty())
  {
    ss << CognitoIdentityProviderEndpoint::ForRegion(config.region);
  }
  else
  {
    ss << config.endpointOverride;
  }

  m_uri = ss.str();
}

AddCustomAttributesOutcome CognitoIdentityProviderClient::AddCustomAttributes(const AddCustomAttributesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AddCustomAttributesOutcome(AddCustomAttributesResult(outcome.GetResult()));
  }
  else
  {
    return AddCustomAttributesOutcome(outcome.GetError());
  }
}

AddCustomAttributesOutcomeCallable CognitoIdentityProviderClient::AddCustomAttributesCallable(const AddCustomAttributesRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AddCustomAttributes(request); } );
}

void CognitoIdentityProviderClient::AddCustomAttributesAsync(const AddCustomAttributesRequest& request, const AddCustomAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AddCustomAttributesAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AddCustomAttributesAsyncHelper(const AddCustomAttributesRequest& request, const AddCustomAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AddCustomAttributes(request), context);
}

AdminConfirmSignUpOutcome CognitoIdentityProviderClient::AdminConfirmSignUp(const AdminConfirmSignUpRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminConfirmSignUpOutcome(AdminConfirmSignUpResult(outcome.GetResult()));
  }
  else
  {
    return AdminConfirmSignUpOutcome(outcome.GetError());
  }
}

AdminConfirmSignUpOutcomeCallable CognitoIdentityProviderClient::AdminConfirmSignUpCallable(const AdminConfirmSignUpRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminConfirmSignUp(request); } );
}

void CognitoIdentityProviderClient::AdminConfirmSignUpAsync(const AdminConfirmSignUpRequest& request, const AdminConfirmSignUpResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminConfirmSignUpAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminConfirmSignUpAsyncHelper(const AdminConfirmSignUpRequest& request, const AdminConfirmSignUpResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminConfirmSignUp(request), context);
}

AdminDeleteUserOutcome CognitoIdentityProviderClient::AdminDeleteUser(const AdminDeleteUserRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminDeleteUserOutcome(NoResult());
  }
  else
  {
    return AdminDeleteUserOutcome(outcome.GetError());
  }
}

AdminDeleteUserOutcomeCallable CognitoIdentityProviderClient::AdminDeleteUserCallable(const AdminDeleteUserRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminDeleteUser(request); } );
}

void CognitoIdentityProviderClient::AdminDeleteUserAsync(const AdminDeleteUserRequest& request, const AdminDeleteUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminDeleteUserAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminDeleteUserAsyncHelper(const AdminDeleteUserRequest& request, const AdminDeleteUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminDeleteUser(request), context);
}

AdminDeleteUserAttributesOutcome CognitoIdentityProviderClient::AdminDeleteUserAttributes(const AdminDeleteUserAttributesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminDeleteUserAttributesOutcome(AdminDeleteUserAttributesResult(outcome.GetResult()));
  }
  else
  {
    return AdminDeleteUserAttributesOutcome(outcome.GetError());
  }
}

AdminDeleteUserAttributesOutcomeCallable CognitoIdentityProviderClient::AdminDeleteUserAttributesCallable(const AdminDeleteUserAttributesRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminDeleteUserAttributes(request); } );
}

void CognitoIdentityProviderClient::AdminDeleteUserAttributesAsync(const AdminDeleteUserAttributesRequest& request, const AdminDeleteUserAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminDeleteUserAttributesAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminDeleteUserAttributesAsyncHelper(const AdminDeleteUserAttributesRequest& request, const AdminDeleteUserAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminDeleteUserAttributes(request), context);
}

AdminDisableUserOutcome CognitoIdentityProviderClient::AdminDisableUser(const AdminDisableUserRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminDisableUserOutcome(AdminDisableUserResult(outcome.GetResult()));
  }
  else
  {
    return AdminDisableUserOutcome(outcome.GetError());
  }
}

AdminDisableUserOutcomeCallable CognitoIdentityProviderClient::AdminDisableUserCallable(const AdminDisableUserRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminDisableUser(request); } );
}

void CognitoIdentityProviderClient::AdminDisableUserAsync(const AdminDisableUserRequest& request, const AdminDisableUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminDisableUserAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminDisableUserAsyncHelper(const AdminDisableUserRequest& request, const AdminDisableUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminDisableUser(request), context);
}

AdminEnableUserOutcome CognitoIdentityProviderClient::AdminEnableUser(const AdminEnableUserRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminEnableUserOutcome(AdminEnableUserResult(outcome.GetResult()));
  }
  else
  {
    return AdminEnableUserOutcome(outcome.GetError());
  }
}

AdminEnableUserOutcomeCallable CognitoIdentityProviderClient::AdminEnableUserCallable(const AdminEnableUserRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminEnableUser(request); } );
}

void CognitoIdentityProviderClient::AdminEnableUserAsync(const AdminEnableUserRequest& request, const AdminEnableUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminEnableUserAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminEnableUserAsyncHelper(const AdminEnableUserRequest& request, const AdminEnableUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminEnableUser(request), context);
}

AdminForgetDeviceOutcome CognitoIdentityProviderClient::AdminForgetDevice(const AdminForgetDeviceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminForgetDeviceOutcome(NoResult());
  }
  else
  {
    return AdminForgetDeviceOutcome(outcome.GetError());
  }
}

AdminForgetDeviceOutcomeCallable CognitoIdentityProviderClient::AdminForgetDeviceCallable(const AdminForgetDeviceRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminForgetDevice(request); } );
}

void CognitoIdentityProviderClient::AdminForgetDeviceAsync(const AdminForgetDeviceRequest& request, const AdminForgetDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminForgetDeviceAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminForgetDeviceAsyncHelper(const AdminForgetDeviceRequest& request, const AdminForgetDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminForgetDevice(request), context);
}

AdminGetDeviceOutcome CognitoIdentityProviderClient::AdminGetDevice(const AdminGetDeviceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminGetDeviceOutcome(AdminGetDeviceResult(outcome.GetResult()));
  }
  else
  {
    return AdminGetDeviceOutcome(outcome.GetError());
  }
}

AdminGetDeviceOutcomeCallable CognitoIdentityProviderClient::AdminGetDeviceCallable(const AdminGetDeviceRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminGetDevice(request); } );
}

void CognitoIdentityProviderClient::AdminGetDeviceAsync(const AdminGetDeviceRequest& request, const AdminGetDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminGetDeviceAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminGetDeviceAsyncHelper(const AdminGetDeviceRequest& request, const AdminGetDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminGetDevice(request), context);
}

AdminGetUserOutcome CognitoIdentityProviderClient::AdminGetUser(const AdminGetUserRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminGetUserOutcome(AdminGetUserResult(outcome.GetResult()));
  }
  else
  {
    return AdminGetUserOutcome(outcome.GetError());
  }
}

AdminGetUserOutcomeCallable CognitoIdentityProviderClient::AdminGetUserCallable(const AdminGetUserRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminGetUser(request); } );
}

void CognitoIdentityProviderClient::AdminGetUserAsync(const AdminGetUserRequest& request, const AdminGetUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminGetUserAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminGetUserAsyncHelper(const AdminGetUserRequest& request, const AdminGetUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminGetUser(request), context);
}

AdminInitiateAuthOutcome CognitoIdentityProviderClient::AdminInitiateAuth(const AdminInitiateAuthRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminInitiateAuthOutcome(AdminInitiateAuthResult(outcome.GetResult()));
  }
  else
  {
    return AdminInitiateAuthOutcome(outcome.GetError());
  }
}

AdminInitiateAuthOutcomeCallable CognitoIdentityProviderClient::AdminInitiateAuthCallable(const AdminInitiateAuthRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminInitiateAuth(request); } );
}

void CognitoIdentityProviderClient::AdminInitiateAuthAsync(const AdminInitiateAuthRequest& request, const AdminInitiateAuthResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminInitiateAuthAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminInitiateAuthAsyncHelper(const AdminInitiateAuthRequest& request, const AdminInitiateAuthResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminInitiateAuth(request), context);
}

AdminListDevicesOutcome CognitoIdentityProviderClient::AdminListDevices(const AdminListDevicesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminListDevicesOutcome(AdminListDevicesResult(outcome.GetResult()));
  }
  else
  {
    return AdminListDevicesOutcome(outcome.GetError());
  }
}

AdminListDevicesOutcomeCallable CognitoIdentityProviderClient::AdminListDevicesCallable(const AdminListDevicesRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminListDevices(request); } );
}

void CognitoIdentityProviderClient::AdminListDevicesAsync(const AdminListDevicesRequest& request, const AdminListDevicesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminListDevicesAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminListDevicesAsyncHelper(const AdminListDevicesRequest& request, const AdminListDevicesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminListDevices(request), context);
}

AdminResetUserPasswordOutcome CognitoIdentityProviderClient::AdminResetUserPassword(const AdminResetUserPasswordRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminResetUserPasswordOutcome(AdminResetUserPasswordResult(outcome.GetResult()));
  }
  else
  {
    return AdminResetUserPasswordOutcome(outcome.GetError());
  }
}

AdminResetUserPasswordOutcomeCallable CognitoIdentityProviderClient::AdminResetUserPasswordCallable(const AdminResetUserPasswordRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminResetUserPassword(request); } );
}

void CognitoIdentityProviderClient::AdminResetUserPasswordAsync(const AdminResetUserPasswordRequest& request, const AdminResetUserPasswordResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminResetUserPasswordAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminResetUserPasswordAsyncHelper(const AdminResetUserPasswordRequest& request, const AdminResetUserPasswordResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminResetUserPassword(request), context);
}

AdminRespondToAuthChallengeOutcome CognitoIdentityProviderClient::AdminRespondToAuthChallenge(const AdminRespondToAuthChallengeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminRespondToAuthChallengeOutcome(AdminRespondToAuthChallengeResult(outcome.GetResult()));
  }
  else
  {
    return AdminRespondToAuthChallengeOutcome(outcome.GetError());
  }
}

AdminRespondToAuthChallengeOutcomeCallable CognitoIdentityProviderClient::AdminRespondToAuthChallengeCallable(const AdminRespondToAuthChallengeRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminRespondToAuthChallenge(request); } );
}

void CognitoIdentityProviderClient::AdminRespondToAuthChallengeAsync(const AdminRespondToAuthChallengeRequest& request, const AdminRespondToAuthChallengeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminRespondToAuthChallengeAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminRespondToAuthChallengeAsyncHelper(const AdminRespondToAuthChallengeRequest& request, const AdminRespondToAuthChallengeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminRespondToAuthChallenge(request), context);
}

AdminSetUserSettingsOutcome CognitoIdentityProviderClient::AdminSetUserSettings(const AdminSetUserSettingsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminSetUserSettingsOutcome(AdminSetUserSettingsResult(outcome.GetResult()));
  }
  else
  {
    return AdminSetUserSettingsOutcome(outcome.GetError());
  }
}

AdminSetUserSettingsOutcomeCallable CognitoIdentityProviderClient::AdminSetUserSettingsCallable(const AdminSetUserSettingsRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminSetUserSettings(request); } );
}

void CognitoIdentityProviderClient::AdminSetUserSettingsAsync(const AdminSetUserSettingsRequest& request, const AdminSetUserSettingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminSetUserSettingsAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminSetUserSettingsAsyncHelper(const AdminSetUserSettingsRequest& request, const AdminSetUserSettingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminSetUserSettings(request), context);
}

AdminUpdateDeviceStatusOutcome CognitoIdentityProviderClient::AdminUpdateDeviceStatus(const AdminUpdateDeviceStatusRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminUpdateDeviceStatusOutcome(AdminUpdateDeviceStatusResult(outcome.GetResult()));
  }
  else
  {
    return AdminUpdateDeviceStatusOutcome(outcome.GetError());
  }
}

AdminUpdateDeviceStatusOutcomeCallable CognitoIdentityProviderClient::AdminUpdateDeviceStatusCallable(const AdminUpdateDeviceStatusRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminUpdateDeviceStatus(request); } );
}

void CognitoIdentityProviderClient::AdminUpdateDeviceStatusAsync(const AdminUpdateDeviceStatusRequest& request, const AdminUpdateDeviceStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminUpdateDeviceStatusAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminUpdateDeviceStatusAsyncHelper(const AdminUpdateDeviceStatusRequest& request, const AdminUpdateDeviceStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminUpdateDeviceStatus(request), context);
}

AdminUpdateUserAttributesOutcome CognitoIdentityProviderClient::AdminUpdateUserAttributes(const AdminUpdateUserAttributesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminUpdateUserAttributesOutcome(AdminUpdateUserAttributesResult(outcome.GetResult()));
  }
  else
  {
    return AdminUpdateUserAttributesOutcome(outcome.GetError());
  }
}

AdminUpdateUserAttributesOutcomeCallable CognitoIdentityProviderClient::AdminUpdateUserAttributesCallable(const AdminUpdateUserAttributesRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminUpdateUserAttributes(request); } );
}

void CognitoIdentityProviderClient::AdminUpdateUserAttributesAsync(const AdminUpdateUserAttributesRequest& request, const AdminUpdateUserAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminUpdateUserAttributesAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminUpdateUserAttributesAsyncHelper(const AdminUpdateUserAttributesRequest& request, const AdminUpdateUserAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminUpdateUserAttributes(request), context);
}

AdminUserGlobalSignOutOutcome CognitoIdentityProviderClient::AdminUserGlobalSignOut(const AdminUserGlobalSignOutRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AdminUserGlobalSignOutOutcome(AdminUserGlobalSignOutResult(outcome.GetResult()));
  }
  else
  {
    return AdminUserGlobalSignOutOutcome(outcome.GetError());
  }
}

AdminUserGlobalSignOutOutcomeCallable CognitoIdentityProviderClient::AdminUserGlobalSignOutCallable(const AdminUserGlobalSignOutRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->AdminUserGlobalSignOut(request); } );
}

void CognitoIdentityProviderClient::AdminUserGlobalSignOutAsync(const AdminUserGlobalSignOutRequest& request, const AdminUserGlobalSignOutResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->AdminUserGlobalSignOutAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::AdminUserGlobalSignOutAsyncHelper(const AdminUserGlobalSignOutRequest& request, const AdminUserGlobalSignOutResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AdminUserGlobalSignOut(request), context);
}

ChangePasswordOutcome CognitoIdentityProviderClient::ChangePassword(const ChangePasswordRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ChangePasswordOutcome(ChangePasswordResult(outcome.GetResult()));
  }
  else
  {
    return ChangePasswordOutcome(outcome.GetError());
  }
}

ChangePasswordOutcomeCallable CognitoIdentityProviderClient::ChangePasswordCallable(const ChangePasswordRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ChangePassword(request); } );
}

void CognitoIdentityProviderClient::ChangePasswordAsync(const ChangePasswordRequest& request, const ChangePasswordResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ChangePasswordAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ChangePasswordAsyncHelper(const ChangePasswordRequest& request, const ChangePasswordResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ChangePassword(request), context);
}

ConfirmDeviceOutcome CognitoIdentityProviderClient::ConfirmDevice(const ConfirmDeviceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ConfirmDeviceOutcome(ConfirmDeviceResult(outcome.GetResult()));
  }
  else
  {
    return ConfirmDeviceOutcome(outcome.GetError());
  }
}

ConfirmDeviceOutcomeCallable CognitoIdentityProviderClient::ConfirmDeviceCallable(const ConfirmDeviceRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ConfirmDevice(request); } );
}

void CognitoIdentityProviderClient::ConfirmDeviceAsync(const ConfirmDeviceRequest& request, const ConfirmDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ConfirmDeviceAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ConfirmDeviceAsyncHelper(const ConfirmDeviceRequest& request, const ConfirmDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ConfirmDevice(request), context);
}

ConfirmForgotPasswordOutcome CognitoIdentityProviderClient::ConfirmForgotPassword(const ConfirmForgotPasswordRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ConfirmForgotPasswordOutcome(ConfirmForgotPasswordResult(outcome.GetResult()));
  }
  else
  {
    return ConfirmForgotPasswordOutcome(outcome.GetError());
  }
}

ConfirmForgotPasswordOutcomeCallable CognitoIdentityProviderClient::ConfirmForgotPasswordCallable(const ConfirmForgotPasswordRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ConfirmForgotPassword(request); } );
}

void CognitoIdentityProviderClient::ConfirmForgotPasswordAsync(const ConfirmForgotPasswordRequest& request, const ConfirmForgotPasswordResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ConfirmForgotPasswordAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ConfirmForgotPasswordAsyncHelper(const ConfirmForgotPasswordRequest& request, const ConfirmForgotPasswordResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ConfirmForgotPassword(request), context);
}

ConfirmSignUpOutcome CognitoIdentityProviderClient::ConfirmSignUp(const ConfirmSignUpRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ConfirmSignUpOutcome(ConfirmSignUpResult(outcome.GetResult()));
  }
  else
  {
    return ConfirmSignUpOutcome(outcome.GetError());
  }
}

ConfirmSignUpOutcomeCallable CognitoIdentityProviderClient::ConfirmSignUpCallable(const ConfirmSignUpRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ConfirmSignUp(request); } );
}

void CognitoIdentityProviderClient::ConfirmSignUpAsync(const ConfirmSignUpRequest& request, const ConfirmSignUpResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ConfirmSignUpAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ConfirmSignUpAsyncHelper(const ConfirmSignUpRequest& request, const ConfirmSignUpResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ConfirmSignUp(request), context);
}

CreateUserPoolOutcome CognitoIdentityProviderClient::CreateUserPool(const CreateUserPoolRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateUserPoolOutcome(CreateUserPoolResult(outcome.GetResult()));
  }
  else
  {
    return CreateUserPoolOutcome(outcome.GetError());
  }
}

CreateUserPoolOutcomeCallable CognitoIdentityProviderClient::CreateUserPoolCallable(const CreateUserPoolRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->CreateUserPool(request); } );
}

void CognitoIdentityProviderClient::CreateUserPoolAsync(const CreateUserPoolRequest& request, const CreateUserPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->CreateUserPoolAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::CreateUserPoolAsyncHelper(const CreateUserPoolRequest& request, const CreateUserPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateUserPool(request), context);
}

CreateUserPoolClientOutcome CognitoIdentityProviderClient::CreateUserPoolClient(const CreateUserPoolClientRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CreateUserPoolClientOutcome(CreateUserPoolClientResult(outcome.GetResult()));
  }
  else
  {
    return CreateUserPoolClientOutcome(outcome.GetError());
  }
}

CreateUserPoolClientOutcomeCallable CognitoIdentityProviderClient::CreateUserPoolClientCallable(const CreateUserPoolClientRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->CreateUserPoolClient(request); } );
}

void CognitoIdentityProviderClient::CreateUserPoolClientAsync(const CreateUserPoolClientRequest& request, const CreateUserPoolClientResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->CreateUserPoolClientAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::CreateUserPoolClientAsyncHelper(const CreateUserPoolClientRequest& request, const CreateUserPoolClientResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateUserPoolClient(request), context);
}

DeleteUserOutcome CognitoIdentityProviderClient::DeleteUser(const DeleteUserRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteUserOutcome(NoResult());
  }
  else
  {
    return DeleteUserOutcome(outcome.GetError());
  }
}

DeleteUserOutcomeCallable CognitoIdentityProviderClient::DeleteUserCallable(const DeleteUserRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->DeleteUser(request); } );
}

void CognitoIdentityProviderClient::DeleteUserAsync(const DeleteUserRequest& request, const DeleteUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteUserAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::DeleteUserAsyncHelper(const DeleteUserRequest& request, const DeleteUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteUser(request), context);
}

DeleteUserAttributesOutcome CognitoIdentityProviderClient::DeleteUserAttributes(const DeleteUserAttributesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteUserAttributesOutcome(DeleteUserAttributesResult(outcome.GetResult()));
  }
  else
  {
    return DeleteUserAttributesOutcome(outcome.GetError());
  }
}

DeleteUserAttributesOutcomeCallable CognitoIdentityProviderClient::DeleteUserAttributesCallable(const DeleteUserAttributesRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->DeleteUserAttributes(request); } );
}

void CognitoIdentityProviderClient::DeleteUserAttributesAsync(const DeleteUserAttributesRequest& request, const DeleteUserAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteUserAttributesAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::DeleteUserAttributesAsyncHelper(const DeleteUserAttributesRequest& request, const DeleteUserAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteUserAttributes(request), context);
}

DeleteUserPoolOutcome CognitoIdentityProviderClient::DeleteUserPool(const DeleteUserPoolRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteUserPoolOutcome(NoResult());
  }
  else
  {
    return DeleteUserPoolOutcome(outcome.GetError());
  }
}

DeleteUserPoolOutcomeCallable CognitoIdentityProviderClient::DeleteUserPoolCallable(const DeleteUserPoolRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->DeleteUserPool(request); } );
}

void CognitoIdentityProviderClient::DeleteUserPoolAsync(const DeleteUserPoolRequest& request, const DeleteUserPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteUserPoolAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::DeleteUserPoolAsyncHelper(const DeleteUserPoolRequest& request, const DeleteUserPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteUserPool(request), context);
}

DeleteUserPoolClientOutcome CognitoIdentityProviderClient::DeleteUserPoolClient(const DeleteUserPoolClientRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DeleteUserPoolClientOutcome(NoResult());
  }
  else
  {
    return DeleteUserPoolClientOutcome(outcome.GetError());
  }
}

DeleteUserPoolClientOutcomeCallable CognitoIdentityProviderClient::DeleteUserPoolClientCallable(const DeleteUserPoolClientRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->DeleteUserPoolClient(request); } );
}

void CognitoIdentityProviderClient::DeleteUserPoolClientAsync(const DeleteUserPoolClientRequest& request, const DeleteUserPoolClientResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteUserPoolClientAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::DeleteUserPoolClientAsyncHelper(const DeleteUserPoolClientRequest& request, const DeleteUserPoolClientResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteUserPoolClient(request), context);
}

DescribeUserPoolOutcome CognitoIdentityProviderClient::DescribeUserPool(const DescribeUserPoolRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeUserPoolOutcome(DescribeUserPoolResult(outcome.GetResult()));
  }
  else
  {
    return DescribeUserPoolOutcome(outcome.GetError());
  }
}

DescribeUserPoolOutcomeCallable CognitoIdentityProviderClient::DescribeUserPoolCallable(const DescribeUserPoolRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->DescribeUserPool(request); } );
}

void CognitoIdentityProviderClient::DescribeUserPoolAsync(const DescribeUserPoolRequest& request, const DescribeUserPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DescribeUserPoolAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::DescribeUserPoolAsyncHelper(const DescribeUserPoolRequest& request, const DescribeUserPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeUserPool(request), context);
}

DescribeUserPoolClientOutcome CognitoIdentityProviderClient::DescribeUserPoolClient(const DescribeUserPoolClientRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return DescribeUserPoolClientOutcome(DescribeUserPoolClientResult(outcome.GetResult()));
  }
  else
  {
    return DescribeUserPoolClientOutcome(outcome.GetError());
  }
}

DescribeUserPoolClientOutcomeCallable CognitoIdentityProviderClient::DescribeUserPoolClientCallable(const DescribeUserPoolClientRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->DescribeUserPoolClient(request); } );
}

void CognitoIdentityProviderClient::DescribeUserPoolClientAsync(const DescribeUserPoolClientRequest& request, const DescribeUserPoolClientResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DescribeUserPoolClientAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::DescribeUserPoolClientAsyncHelper(const DescribeUserPoolClientRequest& request, const DescribeUserPoolClientResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DescribeUserPoolClient(request), context);
}

ForgetDeviceOutcome CognitoIdentityProviderClient::ForgetDevice(const ForgetDeviceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ForgetDeviceOutcome(NoResult());
  }
  else
  {
    return ForgetDeviceOutcome(outcome.GetError());
  }
}

ForgetDeviceOutcomeCallable CognitoIdentityProviderClient::ForgetDeviceCallable(const ForgetDeviceRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ForgetDevice(request); } );
}

void CognitoIdentityProviderClient::ForgetDeviceAsync(const ForgetDeviceRequest& request, const ForgetDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ForgetDeviceAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ForgetDeviceAsyncHelper(const ForgetDeviceRequest& request, const ForgetDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ForgetDevice(request), context);
}

ForgotPasswordOutcome CognitoIdentityProviderClient::ForgotPassword(const ForgotPasswordRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ForgotPasswordOutcome(ForgotPasswordResult(outcome.GetResult()));
  }
  else
  {
    return ForgotPasswordOutcome(outcome.GetError());
  }
}

ForgotPasswordOutcomeCallable CognitoIdentityProviderClient::ForgotPasswordCallable(const ForgotPasswordRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ForgotPassword(request); } );
}

void CognitoIdentityProviderClient::ForgotPasswordAsync(const ForgotPasswordRequest& request, const ForgotPasswordResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ForgotPasswordAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ForgotPasswordAsyncHelper(const ForgotPasswordRequest& request, const ForgotPasswordResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ForgotPassword(request), context);
}

GetDeviceOutcome CognitoIdentityProviderClient::GetDevice(const GetDeviceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return GetDeviceOutcome(GetDeviceResult(outcome.GetResult()));
  }
  else
  {
    return GetDeviceOutcome(outcome.GetError());
  }
}

GetDeviceOutcomeCallable CognitoIdentityProviderClient::GetDeviceCallable(const GetDeviceRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->GetDevice(request); } );
}

void CognitoIdentityProviderClient::GetDeviceAsync(const GetDeviceRequest& request, const GetDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetDeviceAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::GetDeviceAsyncHelper(const GetDeviceRequest& request, const GetDeviceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetDevice(request), context);
}

GetUserOutcome CognitoIdentityProviderClient::GetUser(const GetUserRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return GetUserOutcome(GetUserResult(outcome.GetResult()));
  }
  else
  {
    return GetUserOutcome(outcome.GetError());
  }
}

GetUserOutcomeCallable CognitoIdentityProviderClient::GetUserCallable(const GetUserRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->GetUser(request); } );
}

void CognitoIdentityProviderClient::GetUserAsync(const GetUserRequest& request, const GetUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetUserAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::GetUserAsyncHelper(const GetUserRequest& request, const GetUserResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetUser(request), context);
}

GetUserAttributeVerificationCodeOutcome CognitoIdentityProviderClient::GetUserAttributeVerificationCode(const GetUserAttributeVerificationCodeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return GetUserAttributeVerificationCodeOutcome(GetUserAttributeVerificationCodeResult(outcome.GetResult()));
  }
  else
  {
    return GetUserAttributeVerificationCodeOutcome(outcome.GetError());
  }
}

GetUserAttributeVerificationCodeOutcomeCallable CognitoIdentityProviderClient::GetUserAttributeVerificationCodeCallable(const GetUserAttributeVerificationCodeRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->GetUserAttributeVerificationCode(request); } );
}

void CognitoIdentityProviderClient::GetUserAttributeVerificationCodeAsync(const GetUserAttributeVerificationCodeRequest& request, const GetUserAttributeVerificationCodeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetUserAttributeVerificationCodeAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::GetUserAttributeVerificationCodeAsyncHelper(const GetUserAttributeVerificationCodeRequest& request, const GetUserAttributeVerificationCodeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetUserAttributeVerificationCode(request), context);
}

GlobalSignOutOutcome CognitoIdentityProviderClient::GlobalSignOut(const GlobalSignOutRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return GlobalSignOutOutcome(GlobalSignOutResult(outcome.GetResult()));
  }
  else
  {
    return GlobalSignOutOutcome(outcome.GetError());
  }
}

GlobalSignOutOutcomeCallable CognitoIdentityProviderClient::GlobalSignOutCallable(const GlobalSignOutRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->GlobalSignOut(request); } );
}

void CognitoIdentityProviderClient::GlobalSignOutAsync(const GlobalSignOutRequest& request, const GlobalSignOutResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GlobalSignOutAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::GlobalSignOutAsyncHelper(const GlobalSignOutRequest& request, const GlobalSignOutResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GlobalSignOut(request), context);
}

InitiateAuthOutcome CognitoIdentityProviderClient::InitiateAuth(const InitiateAuthRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return InitiateAuthOutcome(InitiateAuthResult(outcome.GetResult()));
  }
  else
  {
    return InitiateAuthOutcome(outcome.GetError());
  }
}

InitiateAuthOutcomeCallable CognitoIdentityProviderClient::InitiateAuthCallable(const InitiateAuthRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->InitiateAuth(request); } );
}

void CognitoIdentityProviderClient::InitiateAuthAsync(const InitiateAuthRequest& request, const InitiateAuthResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->InitiateAuthAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::InitiateAuthAsyncHelper(const InitiateAuthRequest& request, const InitiateAuthResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, InitiateAuth(request), context);
}

ListDevicesOutcome CognitoIdentityProviderClient::ListDevices(const ListDevicesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ListDevicesOutcome(ListDevicesResult(outcome.GetResult()));
  }
  else
  {
    return ListDevicesOutcome(outcome.GetError());
  }
}

ListDevicesOutcomeCallable CognitoIdentityProviderClient::ListDevicesCallable(const ListDevicesRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ListDevices(request); } );
}

void CognitoIdentityProviderClient::ListDevicesAsync(const ListDevicesRequest& request, const ListDevicesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ListDevicesAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ListDevicesAsyncHelper(const ListDevicesRequest& request, const ListDevicesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ListDevices(request), context);
}

ListUserPoolClientsOutcome CognitoIdentityProviderClient::ListUserPoolClients(const ListUserPoolClientsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ListUserPoolClientsOutcome(ListUserPoolClientsResult(outcome.GetResult()));
  }
  else
  {
    return ListUserPoolClientsOutcome(outcome.GetError());
  }
}

ListUserPoolClientsOutcomeCallable CognitoIdentityProviderClient::ListUserPoolClientsCallable(const ListUserPoolClientsRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ListUserPoolClients(request); } );
}

void CognitoIdentityProviderClient::ListUserPoolClientsAsync(const ListUserPoolClientsRequest& request, const ListUserPoolClientsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ListUserPoolClientsAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ListUserPoolClientsAsyncHelper(const ListUserPoolClientsRequest& request, const ListUserPoolClientsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ListUserPoolClients(request), context);
}

ListUserPoolsOutcome CognitoIdentityProviderClient::ListUserPools(const ListUserPoolsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ListUserPoolsOutcome(ListUserPoolsResult(outcome.GetResult()));
  }
  else
  {
    return ListUserPoolsOutcome(outcome.GetError());
  }
}

ListUserPoolsOutcomeCallable CognitoIdentityProviderClient::ListUserPoolsCallable(const ListUserPoolsRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ListUserPools(request); } );
}

void CognitoIdentityProviderClient::ListUserPoolsAsync(const ListUserPoolsRequest& request, const ListUserPoolsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ListUserPoolsAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ListUserPoolsAsyncHelper(const ListUserPoolsRequest& request, const ListUserPoolsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ListUserPools(request), context);
}

ListUsersOutcome CognitoIdentityProviderClient::ListUsers(const ListUsersRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ListUsersOutcome(ListUsersResult(outcome.GetResult()));
  }
  else
  {
    return ListUsersOutcome(outcome.GetError());
  }
}

ListUsersOutcomeCallable CognitoIdentityProviderClient::ListUsersCallable(const ListUsersRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ListUsers(request); } );
}

void CognitoIdentityProviderClient::ListUsersAsync(const ListUsersRequest& request, const ListUsersResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ListUsersAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ListUsersAsyncHelper(const ListUsersRequest& request, const ListUsersResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ListUsers(request), context);
}

ResendConfirmationCodeOutcome CognitoIdentityProviderClient::ResendConfirmationCode(const ResendConfirmationCodeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ResendConfirmationCodeOutcome(ResendConfirmationCodeResult(outcome.GetResult()));
  }
  else
  {
    return ResendConfirmationCodeOutcome(outcome.GetError());
  }
}

ResendConfirmationCodeOutcomeCallable CognitoIdentityProviderClient::ResendConfirmationCodeCallable(const ResendConfirmationCodeRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->ResendConfirmationCode(request); } );
}

void CognitoIdentityProviderClient::ResendConfirmationCodeAsync(const ResendConfirmationCodeRequest& request, const ResendConfirmationCodeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->ResendConfirmationCodeAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::ResendConfirmationCodeAsyncHelper(const ResendConfirmationCodeRequest& request, const ResendConfirmationCodeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ResendConfirmationCode(request), context);
}

RespondToAuthChallengeOutcome CognitoIdentityProviderClient::RespondToAuthChallenge(const RespondToAuthChallengeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return RespondToAuthChallengeOutcome(RespondToAuthChallengeResult(outcome.GetResult()));
  }
  else
  {
    return RespondToAuthChallengeOutcome(outcome.GetError());
  }
}

RespondToAuthChallengeOutcomeCallable CognitoIdentityProviderClient::RespondToAuthChallengeCallable(const RespondToAuthChallengeRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->RespondToAuthChallenge(request); } );
}

void CognitoIdentityProviderClient::RespondToAuthChallengeAsync(const RespondToAuthChallengeRequest& request, const RespondToAuthChallengeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->RespondToAuthChallengeAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::RespondToAuthChallengeAsyncHelper(const RespondToAuthChallengeRequest& request, const RespondToAuthChallengeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, RespondToAuthChallenge(request), context);
}

SetUserSettingsOutcome CognitoIdentityProviderClient::SetUserSettings(const SetUserSettingsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return SetUserSettingsOutcome(SetUserSettingsResult(outcome.GetResult()));
  }
  else
  {
    return SetUserSettingsOutcome(outcome.GetError());
  }
}

SetUserSettingsOutcomeCallable CognitoIdentityProviderClient::SetUserSettingsCallable(const SetUserSettingsRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->SetUserSettings(request); } );
}

void CognitoIdentityProviderClient::SetUserSettingsAsync(const SetUserSettingsRequest& request, const SetUserSettingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->SetUserSettingsAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::SetUserSettingsAsyncHelper(const SetUserSettingsRequest& request, const SetUserSettingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, SetUserSettings(request), context);
}

SignUpOutcome CognitoIdentityProviderClient::SignUp(const SignUpRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return SignUpOutcome(SignUpResult(outcome.GetResult()));
  }
  else
  {
    return SignUpOutcome(outcome.GetError());
  }
}

SignUpOutcomeCallable CognitoIdentityProviderClient::SignUpCallable(const SignUpRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->SignUp(request); } );
}

void CognitoIdentityProviderClient::SignUpAsync(const SignUpRequest& request, const SignUpResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->SignUpAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::SignUpAsyncHelper(const SignUpRequest& request, const SignUpResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, SignUp(request), context);
}

UpdateDeviceStatusOutcome CognitoIdentityProviderClient::UpdateDeviceStatus(const UpdateDeviceStatusRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return UpdateDeviceStatusOutcome(UpdateDeviceStatusResult(outcome.GetResult()));
  }
  else
  {
    return UpdateDeviceStatusOutcome(outcome.GetError());
  }
}

UpdateDeviceStatusOutcomeCallable CognitoIdentityProviderClient::UpdateDeviceStatusCallable(const UpdateDeviceStatusRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->UpdateDeviceStatus(request); } );
}

void CognitoIdentityProviderClient::UpdateDeviceStatusAsync(const UpdateDeviceStatusRequest& request, const UpdateDeviceStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateDeviceStatusAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::UpdateDeviceStatusAsyncHelper(const UpdateDeviceStatusRequest& request, const UpdateDeviceStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateDeviceStatus(request), context);
}

UpdateUserAttributesOutcome CognitoIdentityProviderClient::UpdateUserAttributes(const UpdateUserAttributesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return UpdateUserAttributesOutcome(UpdateUserAttributesResult(outcome.GetResult()));
  }
  else
  {
    return UpdateUserAttributesOutcome(outcome.GetError());
  }
}

UpdateUserAttributesOutcomeCallable CognitoIdentityProviderClient::UpdateUserAttributesCallable(const UpdateUserAttributesRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->UpdateUserAttributes(request); } );
}

void CognitoIdentityProviderClient::UpdateUserAttributesAsync(const UpdateUserAttributesRequest& request, const UpdateUserAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateUserAttributesAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::UpdateUserAttributesAsyncHelper(const UpdateUserAttributesRequest& request, const UpdateUserAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateUserAttributes(request), context);
}

UpdateUserPoolOutcome CognitoIdentityProviderClient::UpdateUserPool(const UpdateUserPoolRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return UpdateUserPoolOutcome(UpdateUserPoolResult(outcome.GetResult()));
  }
  else
  {
    return UpdateUserPoolOutcome(outcome.GetError());
  }
}

UpdateUserPoolOutcomeCallable CognitoIdentityProviderClient::UpdateUserPoolCallable(const UpdateUserPoolRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->UpdateUserPool(request); } );
}

void CognitoIdentityProviderClient::UpdateUserPoolAsync(const UpdateUserPoolRequest& request, const UpdateUserPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateUserPoolAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::UpdateUserPoolAsyncHelper(const UpdateUserPoolRequest& request, const UpdateUserPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateUserPool(request), context);
}

UpdateUserPoolClientOutcome CognitoIdentityProviderClient::UpdateUserPoolClient(const UpdateUserPoolClientRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return UpdateUserPoolClientOutcome(UpdateUserPoolClientResult(outcome.GetResult()));
  }
  else
  {
    return UpdateUserPoolClientOutcome(outcome.GetError());
  }
}

UpdateUserPoolClientOutcomeCallable CognitoIdentityProviderClient::UpdateUserPoolClientCallable(const UpdateUserPoolClientRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->UpdateUserPoolClient(request); } );
}

void CognitoIdentityProviderClient::UpdateUserPoolClientAsync(const UpdateUserPoolClientRequest& request, const UpdateUserPoolClientResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateUserPoolClientAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::UpdateUserPoolClientAsyncHelper(const UpdateUserPoolClientRequest& request, const UpdateUserPoolClientResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateUserPoolClient(request), context);
}

VerifyUserAttributeOutcome CognitoIdentityProviderClient::VerifyUserAttribute(const VerifyUserAttributeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";

  JsonOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return VerifyUserAttributeOutcome(VerifyUserAttributeResult(outcome.GetResult()));
  }
  else
  {
    return VerifyUserAttributeOutcome(outcome.GetError());
  }
}

VerifyUserAttributeOutcomeCallable CognitoIdentityProviderClient::VerifyUserAttributeCallable(const VerifyUserAttributeRequest& request) const
{
  return std::async(std::launch::async, [this, request](){ return this->VerifyUserAttribute(request); } );
}

void CognitoIdentityProviderClient::VerifyUserAttributeAsync(const VerifyUserAttributeRequest& request, const VerifyUserAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->VerifyUserAttributeAsyncHelper( request, handler, context ); } );
}

void CognitoIdentityProviderClient::VerifyUserAttributeAsyncHelper(const VerifyUserAttributeRequest& request, const VerifyUserAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, VerifyUserAttribute(request), context);
}

