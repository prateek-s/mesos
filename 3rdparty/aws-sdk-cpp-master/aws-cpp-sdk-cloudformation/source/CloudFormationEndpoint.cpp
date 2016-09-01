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
#include <aws/cloudformation/CloudFormationEndpoint.h>
#include <aws/core/utils/memory/stl/AWSMap.h>

using namespace Aws;
using namespace Aws::CloudFormation;

namespace Aws
{
namespace CloudFormation
{
namespace CloudFormationEndpoint
{
  Aws::String ForRegion(Region region)
  {
    switch(region)
    {
     case Region::US_EAST_1:
        return "cloudformation.us-east-1.amazonaws.com";
     case Region::US_WEST_1:
        return "cloudformation.us-west-1.amazonaws.com";
     case Region::US_WEST_2:
        return "cloudformation.us-west-2.amazonaws.com";
     case Region::EU_WEST_1:
        return "cloudformation.eu-west-1.amazonaws.com";
     case Region::EU_CENTRAL_1:
        return "cloudformation.eu-central-1.amazonaws.com";
     case Region::AP_SOUTHEAST_1:
        return "cloudformation.ap-southeast-1.amazonaws.com";
     case Region::AP_SOUTHEAST_2:
        return "cloudformation.ap-southeast-2.amazonaws.com";
     case Region::AP_NORTHEAST_1:
        return "cloudformation.ap-northeast-1.amazonaws.com";
     case Region::AP_NORTHEAST_2:
        return "cloudformation.ap-northeast-2.amazonaws.com";
     case Region::SA_EAST_1:
        return "cloudformation.sa-east-1.amazonaws.com";
     case Region::AP_SOUTH_1:
        return "cloudformation.ap-south-1.amazonaws.com";
     default:
        return "cloudformation.us-east-1.amazonaws.com";
    }
  }

} // namespace CloudFormationEndpoint
} // namespace CloudFormation
} // namespace Aws

