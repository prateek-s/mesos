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
#pragma once
#include <aws/route53/Route53_EXPORTS.h>
#include <aws/route53/Route53Request.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/route53/model/VPC.h>

namespace Aws
{
namespace Route53
{
namespace Model
{

  /**
   * <p>A complex type that contains information about the request to disassociate a
   * VPC from an hosted zone.</p>
   */
  class AWS_ROUTE53_API DisassociateVPCFromHostedZoneRequest : public Route53Request
  {
  public:
    DisassociateVPCFromHostedZoneRequest();
    Aws::String SerializePayload() const override;

    /**
     * <p>The ID of the hosted zone you want to disassociate your VPC from.</p> <p>Note
     * that you cannot disassociate the last VPC from a hosted zone.</p>
     */
    inline const Aws::String& GetHostedZoneId() const{ return m_hostedZoneId; }

    /**
     * <p>The ID of the hosted zone you want to disassociate your VPC from.</p> <p>Note
     * that you cannot disassociate the last VPC from a hosted zone.</p>
     */
    inline void SetHostedZoneId(const Aws::String& value) { m_hostedZoneIdHasBeenSet = true; m_hostedZoneId = value; }

    /**
     * <p>The ID of the hosted zone you want to disassociate your VPC from.</p> <p>Note
     * that you cannot disassociate the last VPC from a hosted zone.</p>
     */
    inline void SetHostedZoneId(Aws::String&& value) { m_hostedZoneIdHasBeenSet = true; m_hostedZoneId = value; }

    /**
     * <p>The ID of the hosted zone you want to disassociate your VPC from.</p> <p>Note
     * that you cannot disassociate the last VPC from a hosted zone.</p>
     */
    inline void SetHostedZoneId(const char* value) { m_hostedZoneIdHasBeenSet = true; m_hostedZoneId.assign(value); }

    /**
     * <p>The ID of the hosted zone you want to disassociate your VPC from.</p> <p>Note
     * that you cannot disassociate the last VPC from a hosted zone.</p>
     */
    inline DisassociateVPCFromHostedZoneRequest& WithHostedZoneId(const Aws::String& value) { SetHostedZoneId(value); return *this;}

    /**
     * <p>The ID of the hosted zone you want to disassociate your VPC from.</p> <p>Note
     * that you cannot disassociate the last VPC from a hosted zone.</p>
     */
    inline DisassociateVPCFromHostedZoneRequest& WithHostedZoneId(Aws::String&& value) { SetHostedZoneId(value); return *this;}

    /**
     * <p>The ID of the hosted zone you want to disassociate your VPC from.</p> <p>Note
     * that you cannot disassociate the last VPC from a hosted zone.</p>
     */
    inline DisassociateVPCFromHostedZoneRequest& WithHostedZoneId(const char* value) { SetHostedZoneId(value); return *this;}

    /**
     * <p>The VPC that you want your hosted zone to be disassociated from. </p>
     */
    inline const VPC& GetVPC() const{ return m_vPC; }

    /**
     * <p>The VPC that you want your hosted zone to be disassociated from. </p>
     */
    inline void SetVPC(const VPC& value) { m_vPCHasBeenSet = true; m_vPC = value; }

    /**
     * <p>The VPC that you want your hosted zone to be disassociated from. </p>
     */
    inline void SetVPC(VPC&& value) { m_vPCHasBeenSet = true; m_vPC = value; }

    /**
     * <p>The VPC that you want your hosted zone to be disassociated from. </p>
     */
    inline DisassociateVPCFromHostedZoneRequest& WithVPC(const VPC& value) { SetVPC(value); return *this;}

    /**
     * <p>The VPC that you want your hosted zone to be disassociated from. </p>
     */
    inline DisassociateVPCFromHostedZoneRequest& WithVPC(VPC&& value) { SetVPC(value); return *this;}

    /**
     * <p><i>Optional:</i> Any comments you want to include about a
     * <code>DisassociateVPCFromHostedZoneRequest</code>.</p>
     */
    inline const Aws::String& GetComment() const{ return m_comment; }

    /**
     * <p><i>Optional:</i> Any comments you want to include about a
     * <code>DisassociateVPCFromHostedZoneRequest</code>.</p>
     */
    inline void SetComment(const Aws::String& value) { m_commentHasBeenSet = true; m_comment = value; }

    /**
     * <p><i>Optional:</i> Any comments you want to include about a
     * <code>DisassociateVPCFromHostedZoneRequest</code>.</p>
     */
    inline void SetComment(Aws::String&& value) { m_commentHasBeenSet = true; m_comment = value; }

    /**
     * <p><i>Optional:</i> Any comments you want to include about a
     * <code>DisassociateVPCFromHostedZoneRequest</code>.</p>
     */
    inline void SetComment(const char* value) { m_commentHasBeenSet = true; m_comment.assign(value); }

    /**
     * <p><i>Optional:</i> Any comments you want to include about a
     * <code>DisassociateVPCFromHostedZoneRequest</code>.</p>
     */
    inline DisassociateVPCFromHostedZoneRequest& WithComment(const Aws::String& value) { SetComment(value); return *this;}

    /**
     * <p><i>Optional:</i> Any comments you want to include about a
     * <code>DisassociateVPCFromHostedZoneRequest</code>.</p>
     */
    inline DisassociateVPCFromHostedZoneRequest& WithComment(Aws::String&& value) { SetComment(value); return *this;}

    /**
     * <p><i>Optional:</i> Any comments you want to include about a
     * <code>DisassociateVPCFromHostedZoneRequest</code>.</p>
     */
    inline DisassociateVPCFromHostedZoneRequest& WithComment(const char* value) { SetComment(value); return *this;}

  private:
    Aws::String m_hostedZoneId;
    bool m_hostedZoneIdHasBeenSet;
    VPC m_vPC;
    bool m_vPCHasBeenSet;
    Aws::String m_comment;
    bool m_commentHasBeenSet;
  };

} // namespace Model
} // namespace Route53
} // namespace Aws
