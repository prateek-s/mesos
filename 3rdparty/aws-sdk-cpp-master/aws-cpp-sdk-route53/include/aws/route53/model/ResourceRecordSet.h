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
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/route53/model/RRType.h>
#include <aws/route53/model/ResourceRecordSetRegion.h>
#include <aws/route53/model/GeoLocation.h>
#include <aws/route53/model/ResourceRecordSetFailover.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/route53/model/AliasTarget.h>
#include <aws/route53/model/ResourceRecord.h>

namespace Aws
{
namespace Utils
{
namespace Xml
{
  class XmlNode;
} // namespace Xml
} // namespace Utils
namespace Route53
{
namespace Model
{

  /**
   * <p>A complex type that contains information about the current resource record
   * set.</p>
   */
  class AWS_ROUTE53_API ResourceRecordSet
  {
  public:
    ResourceRecordSet();
    ResourceRecordSet(const Aws::Utils::Xml::XmlNode& xmlNode);
    ResourceRecordSet& operator=(const Aws::Utils::Xml::XmlNode& xmlNode);

    void AddToNode(Aws::Utils::Xml::XmlNode& parentNode) const;

    /**
     * <p>The name of the domain you want to perform the action on.</p> <p>Enter a
     * fully qualified domain name, for example, <code>www.example.com</code>. You can
     * optionally include a trailing dot. If you omit the trailing dot, Amazon Route 53
     * still assumes that the domain name that you specify is fully qualified. This
     * means that Amazon Route 53 treats <code>www.example.com</code> (without a
     * trailing dot) and <code>www.example.com.</code> (with a trailing dot) as
     * identical.</p> <p>For information about how to specify characters other than
     * a-z, 0-9, and - (hyphen) and how to specify internationalized domain names, see
     * <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html">DNS
     * Domain Name Format</a> in the <i>Amazon Route 53 Developer Guide</i>.</p> <p>You
     * can use an asterisk (*) character in the name. DNS treats the * character either
     * as a wildcard or as the * character (ASCII 42), depending on where it appears in
     * the name. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html#domain-name-format-asterisk">Using
     * an Asterisk (*) in the Names of Hosted Zones and Resource Record Sets</a> in the
     * <i>Amazon Route 53 Developer Guide</i></p> <important>You can't use the *
     * wildcard for resource records sets that have a type of NS.</important>
     */
    inline const Aws::String& GetName() const{ return m_name; }

    /**
     * <p>The name of the domain you want to perform the action on.</p> <p>Enter a
     * fully qualified domain name, for example, <code>www.example.com</code>. You can
     * optionally include a trailing dot. If you omit the trailing dot, Amazon Route 53
     * still assumes that the domain name that you specify is fully qualified. This
     * means that Amazon Route 53 treats <code>www.example.com</code> (without a
     * trailing dot) and <code>www.example.com.</code> (with a trailing dot) as
     * identical.</p> <p>For information about how to specify characters other than
     * a-z, 0-9, and - (hyphen) and how to specify internationalized domain names, see
     * <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html">DNS
     * Domain Name Format</a> in the <i>Amazon Route 53 Developer Guide</i>.</p> <p>You
     * can use an asterisk (*) character in the name. DNS treats the * character either
     * as a wildcard or as the * character (ASCII 42), depending on where it appears in
     * the name. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html#domain-name-format-asterisk">Using
     * an Asterisk (*) in the Names of Hosted Zones and Resource Record Sets</a> in the
     * <i>Amazon Route 53 Developer Guide</i></p> <important>You can't use the *
     * wildcard for resource records sets that have a type of NS.</important>
     */
    inline void SetName(const Aws::String& value) { m_nameHasBeenSet = true; m_name = value; }

    /**
     * <p>The name of the domain you want to perform the action on.</p> <p>Enter a
     * fully qualified domain name, for example, <code>www.example.com</code>. You can
     * optionally include a trailing dot. If you omit the trailing dot, Amazon Route 53
     * still assumes that the domain name that you specify is fully qualified. This
     * means that Amazon Route 53 treats <code>www.example.com</code> (without a
     * trailing dot) and <code>www.example.com.</code> (with a trailing dot) as
     * identical.</p> <p>For information about how to specify characters other than
     * a-z, 0-9, and - (hyphen) and how to specify internationalized domain names, see
     * <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html">DNS
     * Domain Name Format</a> in the <i>Amazon Route 53 Developer Guide</i>.</p> <p>You
     * can use an asterisk (*) character in the name. DNS treats the * character either
     * as a wildcard or as the * character (ASCII 42), depending on where it appears in
     * the name. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html#domain-name-format-asterisk">Using
     * an Asterisk (*) in the Names of Hosted Zones and Resource Record Sets</a> in the
     * <i>Amazon Route 53 Developer Guide</i></p> <important>You can't use the *
     * wildcard for resource records sets that have a type of NS.</important>
     */
    inline void SetName(Aws::String&& value) { m_nameHasBeenSet = true; m_name = value; }

    /**
     * <p>The name of the domain you want to perform the action on.</p> <p>Enter a
     * fully qualified domain name, for example, <code>www.example.com</code>. You can
     * optionally include a trailing dot. If you omit the trailing dot, Amazon Route 53
     * still assumes that the domain name that you specify is fully qualified. This
     * means that Amazon Route 53 treats <code>www.example.com</code> (without a
     * trailing dot) and <code>www.example.com.</code> (with a trailing dot) as
     * identical.</p> <p>For information about how to specify characters other than
     * a-z, 0-9, and - (hyphen) and how to specify internationalized domain names, see
     * <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html">DNS
     * Domain Name Format</a> in the <i>Amazon Route 53 Developer Guide</i>.</p> <p>You
     * can use an asterisk (*) character in the name. DNS treats the * character either
     * as a wildcard or as the * character (ASCII 42), depending on where it appears in
     * the name. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html#domain-name-format-asterisk">Using
     * an Asterisk (*) in the Names of Hosted Zones and Resource Record Sets</a> in the
     * <i>Amazon Route 53 Developer Guide</i></p> <important>You can't use the *
     * wildcard for resource records sets that have a type of NS.</important>
     */
    inline void SetName(const char* value) { m_nameHasBeenSet = true; m_name.assign(value); }

    /**
     * <p>The name of the domain you want to perform the action on.</p> <p>Enter a
     * fully qualified domain name, for example, <code>www.example.com</code>. You can
     * optionally include a trailing dot. If you omit the trailing dot, Amazon Route 53
     * still assumes that the domain name that you specify is fully qualified. This
     * means that Amazon Route 53 treats <code>www.example.com</code> (without a
     * trailing dot) and <code>www.example.com.</code> (with a trailing dot) as
     * identical.</p> <p>For information about how to specify characters other than
     * a-z, 0-9, and - (hyphen) and how to specify internationalized domain names, see
     * <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html">DNS
     * Domain Name Format</a> in the <i>Amazon Route 53 Developer Guide</i>.</p> <p>You
     * can use an asterisk (*) character in the name. DNS treats the * character either
     * as a wildcard or as the * character (ASCII 42), depending on where it appears in
     * the name. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html#domain-name-format-asterisk">Using
     * an Asterisk (*) in the Names of Hosted Zones and Resource Record Sets</a> in the
     * <i>Amazon Route 53 Developer Guide</i></p> <important>You can't use the *
     * wildcard for resource records sets that have a type of NS.</important>
     */
    inline ResourceRecordSet& WithName(const Aws::String& value) { SetName(value); return *this;}

    /**
     * <p>The name of the domain you want to perform the action on.</p> <p>Enter a
     * fully qualified domain name, for example, <code>www.example.com</code>. You can
     * optionally include a trailing dot. If you omit the trailing dot, Amazon Route 53
     * still assumes that the domain name that you specify is fully qualified. This
     * means that Amazon Route 53 treats <code>www.example.com</code> (without a
     * trailing dot) and <code>www.example.com.</code> (with a trailing dot) as
     * identical.</p> <p>For information about how to specify characters other than
     * a-z, 0-9, and - (hyphen) and how to specify internationalized domain names, see
     * <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html">DNS
     * Domain Name Format</a> in the <i>Amazon Route 53 Developer Guide</i>.</p> <p>You
     * can use an asterisk (*) character in the name. DNS treats the * character either
     * as a wildcard or as the * character (ASCII 42), depending on where it appears in
     * the name. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html#domain-name-format-asterisk">Using
     * an Asterisk (*) in the Names of Hosted Zones and Resource Record Sets</a> in the
     * <i>Amazon Route 53 Developer Guide</i></p> <important>You can't use the *
     * wildcard for resource records sets that have a type of NS.</important>
     */
    inline ResourceRecordSet& WithName(Aws::String&& value) { SetName(value); return *this;}

    /**
     * <p>The name of the domain you want to perform the action on.</p> <p>Enter a
     * fully qualified domain name, for example, <code>www.example.com</code>. You can
     * optionally include a trailing dot. If you omit the trailing dot, Amazon Route 53
     * still assumes that the domain name that you specify is fully qualified. This
     * means that Amazon Route 53 treats <code>www.example.com</code> (without a
     * trailing dot) and <code>www.example.com.</code> (with a trailing dot) as
     * identical.</p> <p>For information about how to specify characters other than
     * a-z, 0-9, and - (hyphen) and how to specify internationalized domain names, see
     * <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html">DNS
     * Domain Name Format</a> in the <i>Amazon Route 53 Developer Guide</i>.</p> <p>You
     * can use an asterisk (*) character in the name. DNS treats the * character either
     * as a wildcard or as the * character (ASCII 42), depending on where it appears in
     * the name. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/DomainNameFormat.html#domain-name-format-asterisk">Using
     * an Asterisk (*) in the Names of Hosted Zones and Resource Record Sets</a> in the
     * <i>Amazon Route 53 Developer Guide</i></p> <important>You can't use the *
     * wildcard for resource records sets that have a type of NS.</important>
     */
    inline ResourceRecordSet& WithName(const char* value) { SetName(value); return *this;}

    /**
     * <p>The DNS record type. For information about different record types and how
     * data is encoded for them, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/ResourceRecordTypes.html">Supported
     * DNS Resource Record Types</a> in the <i>Amazon Route 53 Developer Guide</i>.</p>
     * <p>Valid values for basic resource record sets: <code>A</code> |
     * <code>AAAA</code> | <code>CNAME</code> | <code>MX</code> | <code>NS</code> |
     * <code>PTR</code> | <code>SOA</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code></p> <p>Values for weighted, latency, geolocation, and failover
     * resource record sets: <code>A</code> | <code>AAAA</code> | <code>CNAME</code> |
     * <code>MX</code> | <code>PTR</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code>. When creating a group of weighted, latency, geolocation, or
     * failover resource record sets, specify the same value for all of the resource
     * record sets in the group.</p> <note>SPF records were formerly used to verify the
     * identity of the sender of email messages. However, we no longer recommend that
     * you create resource record sets for which the value of <code>Type</code> is
     * <code>SPF</code>. RFC 7208, <i>Sender Policy Framework (SPF) for Authorizing Use
     * of Domains in Email, Version 1</i>, has been updated to say, "...[I]ts existence
     * and mechanism defined in [RFC4408] have led to some interoperability issues.
     * Accordingly, its use is no longer appropriate for SPF version 1; implementations
     * are not to use it." In RFC 7208, see section 14.1, <a
     * href="http://tools.ietf.org/html/rfc7208#section-14.1">The SPF DNS Record
     * Type</a>.</note> <p>Values for alias resource record sets:</p> <ul>
     * <li><b>CloudFront distributions:</b> <code>A</code></li> <li><b>ELB load
     * balancers:</b> <code>A</code> | <code>AAAA</code></li> <li><b>Amazon S3
     * buckets:</b> A</li> <li><b>Another resource record set in this hosted zone:</b>
     * Specify the type of the resource record set for which you're creating the alias.
     * Specify any value except <code>NS</code> or <code>SOA</code>.</li> </ul>
     */
    inline const RRType& GetType() const{ return m_type; }

    /**
     * <p>The DNS record type. For information about different record types and how
     * data is encoded for them, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/ResourceRecordTypes.html">Supported
     * DNS Resource Record Types</a> in the <i>Amazon Route 53 Developer Guide</i>.</p>
     * <p>Valid values for basic resource record sets: <code>A</code> |
     * <code>AAAA</code> | <code>CNAME</code> | <code>MX</code> | <code>NS</code> |
     * <code>PTR</code> | <code>SOA</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code></p> <p>Values for weighted, latency, geolocation, and failover
     * resource record sets: <code>A</code> | <code>AAAA</code> | <code>CNAME</code> |
     * <code>MX</code> | <code>PTR</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code>. When creating a group of weighted, latency, geolocation, or
     * failover resource record sets, specify the same value for all of the resource
     * record sets in the group.</p> <note>SPF records were formerly used to verify the
     * identity of the sender of email messages. However, we no longer recommend that
     * you create resource record sets for which the value of <code>Type</code> is
     * <code>SPF</code>. RFC 7208, <i>Sender Policy Framework (SPF) for Authorizing Use
     * of Domains in Email, Version 1</i>, has been updated to say, "...[I]ts existence
     * and mechanism defined in [RFC4408] have led to some interoperability issues.
     * Accordingly, its use is no longer appropriate for SPF version 1; implementations
     * are not to use it." In RFC 7208, see section 14.1, <a
     * href="http://tools.ietf.org/html/rfc7208#section-14.1">The SPF DNS Record
     * Type</a>.</note> <p>Values for alias resource record sets:</p> <ul>
     * <li><b>CloudFront distributions:</b> <code>A</code></li> <li><b>ELB load
     * balancers:</b> <code>A</code> | <code>AAAA</code></li> <li><b>Amazon S3
     * buckets:</b> A</li> <li><b>Another resource record set in this hosted zone:</b>
     * Specify the type of the resource record set for which you're creating the alias.
     * Specify any value except <code>NS</code> or <code>SOA</code>.</li> </ul>
     */
    inline void SetType(const RRType& value) { m_typeHasBeenSet = true; m_type = value; }

    /**
     * <p>The DNS record type. For information about different record types and how
     * data is encoded for them, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/ResourceRecordTypes.html">Supported
     * DNS Resource Record Types</a> in the <i>Amazon Route 53 Developer Guide</i>.</p>
     * <p>Valid values for basic resource record sets: <code>A</code> |
     * <code>AAAA</code> | <code>CNAME</code> | <code>MX</code> | <code>NS</code> |
     * <code>PTR</code> | <code>SOA</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code></p> <p>Values for weighted, latency, geolocation, and failover
     * resource record sets: <code>A</code> | <code>AAAA</code> | <code>CNAME</code> |
     * <code>MX</code> | <code>PTR</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code>. When creating a group of weighted, latency, geolocation, or
     * failover resource record sets, specify the same value for all of the resource
     * record sets in the group.</p> <note>SPF records were formerly used to verify the
     * identity of the sender of email messages. However, we no longer recommend that
     * you create resource record sets for which the value of <code>Type</code> is
     * <code>SPF</code>. RFC 7208, <i>Sender Policy Framework (SPF) for Authorizing Use
     * of Domains in Email, Version 1</i>, has been updated to say, "...[I]ts existence
     * and mechanism defined in [RFC4408] have led to some interoperability issues.
     * Accordingly, its use is no longer appropriate for SPF version 1; implementations
     * are not to use it." In RFC 7208, see section 14.1, <a
     * href="http://tools.ietf.org/html/rfc7208#section-14.1">The SPF DNS Record
     * Type</a>.</note> <p>Values for alias resource record sets:</p> <ul>
     * <li><b>CloudFront distributions:</b> <code>A</code></li> <li><b>ELB load
     * balancers:</b> <code>A</code> | <code>AAAA</code></li> <li><b>Amazon S3
     * buckets:</b> A</li> <li><b>Another resource record set in this hosted zone:</b>
     * Specify the type of the resource record set for which you're creating the alias.
     * Specify any value except <code>NS</code> or <code>SOA</code>.</li> </ul>
     */
    inline void SetType(RRType&& value) { m_typeHasBeenSet = true; m_type = value; }

    /**
     * <p>The DNS record type. For information about different record types and how
     * data is encoded for them, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/ResourceRecordTypes.html">Supported
     * DNS Resource Record Types</a> in the <i>Amazon Route 53 Developer Guide</i>.</p>
     * <p>Valid values for basic resource record sets: <code>A</code> |
     * <code>AAAA</code> | <code>CNAME</code> | <code>MX</code> | <code>NS</code> |
     * <code>PTR</code> | <code>SOA</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code></p> <p>Values for weighted, latency, geolocation, and failover
     * resource record sets: <code>A</code> | <code>AAAA</code> | <code>CNAME</code> |
     * <code>MX</code> | <code>PTR</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code>. When creating a group of weighted, latency, geolocation, or
     * failover resource record sets, specify the same value for all of the resource
     * record sets in the group.</p> <note>SPF records were formerly used to verify the
     * identity of the sender of email messages. However, we no longer recommend that
     * you create resource record sets for which the value of <code>Type</code> is
     * <code>SPF</code>. RFC 7208, <i>Sender Policy Framework (SPF) for Authorizing Use
     * of Domains in Email, Version 1</i>, has been updated to say, "...[I]ts existence
     * and mechanism defined in [RFC4408] have led to some interoperability issues.
     * Accordingly, its use is no longer appropriate for SPF version 1; implementations
     * are not to use it." In RFC 7208, see section 14.1, <a
     * href="http://tools.ietf.org/html/rfc7208#section-14.1">The SPF DNS Record
     * Type</a>.</note> <p>Values for alias resource record sets:</p> <ul>
     * <li><b>CloudFront distributions:</b> <code>A</code></li> <li><b>ELB load
     * balancers:</b> <code>A</code> | <code>AAAA</code></li> <li><b>Amazon S3
     * buckets:</b> A</li> <li><b>Another resource record set in this hosted zone:</b>
     * Specify the type of the resource record set for which you're creating the alias.
     * Specify any value except <code>NS</code> or <code>SOA</code>.</li> </ul>
     */
    inline ResourceRecordSet& WithType(const RRType& value) { SetType(value); return *this;}

    /**
     * <p>The DNS record type. For information about different record types and how
     * data is encoded for them, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/ResourceRecordTypes.html">Supported
     * DNS Resource Record Types</a> in the <i>Amazon Route 53 Developer Guide</i>.</p>
     * <p>Valid values for basic resource record sets: <code>A</code> |
     * <code>AAAA</code> | <code>CNAME</code> | <code>MX</code> | <code>NS</code> |
     * <code>PTR</code> | <code>SOA</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code></p> <p>Values for weighted, latency, geolocation, and failover
     * resource record sets: <code>A</code> | <code>AAAA</code> | <code>CNAME</code> |
     * <code>MX</code> | <code>PTR</code> | <code>SPF</code> | <code>SRV</code> |
     * <code>TXT</code>. When creating a group of weighted, latency, geolocation, or
     * failover resource record sets, specify the same value for all of the resource
     * record sets in the group.</p> <note>SPF records were formerly used to verify the
     * identity of the sender of email messages. However, we no longer recommend that
     * you create resource record sets for which the value of <code>Type</code> is
     * <code>SPF</code>. RFC 7208, <i>Sender Policy Framework (SPF) for Authorizing Use
     * of Domains in Email, Version 1</i>, has been updated to say, "...[I]ts existence
     * and mechanism defined in [RFC4408] have led to some interoperability issues.
     * Accordingly, its use is no longer appropriate for SPF version 1; implementations
     * are not to use it." In RFC 7208, see section 14.1, <a
     * href="http://tools.ietf.org/html/rfc7208#section-14.1">The SPF DNS Record
     * Type</a>.</note> <p>Values for alias resource record sets:</p> <ul>
     * <li><b>CloudFront distributions:</b> <code>A</code></li> <li><b>ELB load
     * balancers:</b> <code>A</code> | <code>AAAA</code></li> <li><b>Amazon S3
     * buckets:</b> A</li> <li><b>Another resource record set in this hosted zone:</b>
     * Specify the type of the resource record set for which you're creating the alias.
     * Specify any value except <code>NS</code> or <code>SOA</code>.</li> </ul>
     */
    inline ResourceRecordSet& WithType(RRType&& value) { SetType(value); return *this;}

    /**
     * <p><i>Weighted, Latency, Geo, and Failover resource record sets only:</i> An
     * identifier that differentiates among multiple resource record sets that have the
     * same combination of DNS name and type. The value of <code>SetIdentifier</code>
     * must be unique for each resource record set that has the same combination of DNS
     * name and type.</p>
     */
    inline const Aws::String& GetSetIdentifier() const{ return m_setIdentifier; }

    /**
     * <p><i>Weighted, Latency, Geo, and Failover resource record sets only:</i> An
     * identifier that differentiates among multiple resource record sets that have the
     * same combination of DNS name and type. The value of <code>SetIdentifier</code>
     * must be unique for each resource record set that has the same combination of DNS
     * name and type.</p>
     */
    inline void SetSetIdentifier(const Aws::String& value) { m_setIdentifierHasBeenSet = true; m_setIdentifier = value; }

    /**
     * <p><i>Weighted, Latency, Geo, and Failover resource record sets only:</i> An
     * identifier that differentiates among multiple resource record sets that have the
     * same combination of DNS name and type. The value of <code>SetIdentifier</code>
     * must be unique for each resource record set that has the same combination of DNS
     * name and type.</p>
     */
    inline void SetSetIdentifier(Aws::String&& value) { m_setIdentifierHasBeenSet = true; m_setIdentifier = value; }

    /**
     * <p><i>Weighted, Latency, Geo, and Failover resource record sets only:</i> An
     * identifier that differentiates among multiple resource record sets that have the
     * same combination of DNS name and type. The value of <code>SetIdentifier</code>
     * must be unique for each resource record set that has the same combination of DNS
     * name and type.</p>
     */
    inline void SetSetIdentifier(const char* value) { m_setIdentifierHasBeenSet = true; m_setIdentifier.assign(value); }

    /**
     * <p><i>Weighted, Latency, Geo, and Failover resource record sets only:</i> An
     * identifier that differentiates among multiple resource record sets that have the
     * same combination of DNS name and type. The value of <code>SetIdentifier</code>
     * must be unique for each resource record set that has the same combination of DNS
     * name and type.</p>
     */
    inline ResourceRecordSet& WithSetIdentifier(const Aws::String& value) { SetSetIdentifier(value); return *this;}

    /**
     * <p><i>Weighted, Latency, Geo, and Failover resource record sets only:</i> An
     * identifier that differentiates among multiple resource record sets that have the
     * same combination of DNS name and type. The value of <code>SetIdentifier</code>
     * must be unique for each resource record set that has the same combination of DNS
     * name and type.</p>
     */
    inline ResourceRecordSet& WithSetIdentifier(Aws::String&& value) { SetSetIdentifier(value); return *this;}

    /**
     * <p><i>Weighted, Latency, Geo, and Failover resource record sets only:</i> An
     * identifier that differentiates among multiple resource record sets that have the
     * same combination of DNS name and type. The value of <code>SetIdentifier</code>
     * must be unique for each resource record set that has the same combination of DNS
     * name and type.</p>
     */
    inline ResourceRecordSet& WithSetIdentifier(const char* value) { SetSetIdentifier(value); return *this;}

    /**
     * <p><i>Weighted resource record sets only:</i> Among resource record sets that
     * have the same combination of DNS name and type, a value that determines the
     * proportion of DNS queries that Amazon Route 53 responds to using the current
     * resource record set. Amazon Route 53 calculates the sum of the weights for the
     * resource record sets that have the same combination of DNS name and type. Amazon
     * Route 53 then responds to queries based on the ratio of a resource's weight to
     * the total. Note the following:</p> <ul> <li>You must specify a value for the
     * <code>Weight</code> element for every weighted resource record set.</li> <li>You
     * can only specify one <code>ResourceRecord</code> per weighted resource record
     * set.</li> <li>You cannot create latency, failover, or geolocation resource
     * record sets that have the same values for the <code>Name</code> and
     * <code>Type</code> elements as weighted resource record sets.</li> <li>You can
     * create a maximum of 100 weighted resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements.</li> <li><p>For
     * weighted (but not weighted alias) resource record sets, if you set
     * <code>Weight</code> to <code>0</code> for a resource record set, Amazon Route 53
     * never responds to queries with the applicable value for that resource record
     * set. However, if you set <code>Weight</code> to <code>0</code> for all resource
     * record sets that have the same combination of DNS name and type, traffic is
     * routed to all resources with equal probability.</p> <p>The effect of setting
     * <code>Weight</code> to <code>0</code> is different when you associate health
     * checks with weighted resource record sets. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/dns-failover-configuring-options.html">Options
     * for Configuring Amazon Route 53 Active-Active and Active-Passive Failover</a> in
     * the <i>Amazon Route 53 Developer Guide</i>.</p> </li> </ul>
     */
    inline long long GetWeight() const{ return m_weight; }

    /**
     * <p><i>Weighted resource record sets only:</i> Among resource record sets that
     * have the same combination of DNS name and type, a value that determines the
     * proportion of DNS queries that Amazon Route 53 responds to using the current
     * resource record set. Amazon Route 53 calculates the sum of the weights for the
     * resource record sets that have the same combination of DNS name and type. Amazon
     * Route 53 then responds to queries based on the ratio of a resource's weight to
     * the total. Note the following:</p> <ul> <li>You must specify a value for the
     * <code>Weight</code> element for every weighted resource record set.</li> <li>You
     * can only specify one <code>ResourceRecord</code> per weighted resource record
     * set.</li> <li>You cannot create latency, failover, or geolocation resource
     * record sets that have the same values for the <code>Name</code> and
     * <code>Type</code> elements as weighted resource record sets.</li> <li>You can
     * create a maximum of 100 weighted resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements.</li> <li><p>For
     * weighted (but not weighted alias) resource record sets, if you set
     * <code>Weight</code> to <code>0</code> for a resource record set, Amazon Route 53
     * never responds to queries with the applicable value for that resource record
     * set. However, if you set <code>Weight</code> to <code>0</code> for all resource
     * record sets that have the same combination of DNS name and type, traffic is
     * routed to all resources with equal probability.</p> <p>The effect of setting
     * <code>Weight</code> to <code>0</code> is different when you associate health
     * checks with weighted resource record sets. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/dns-failover-configuring-options.html">Options
     * for Configuring Amazon Route 53 Active-Active and Active-Passive Failover</a> in
     * the <i>Amazon Route 53 Developer Guide</i>.</p> </li> </ul>
     */
    inline void SetWeight(long long value) { m_weightHasBeenSet = true; m_weight = value; }

    /**
     * <p><i>Weighted resource record sets only:</i> Among resource record sets that
     * have the same combination of DNS name and type, a value that determines the
     * proportion of DNS queries that Amazon Route 53 responds to using the current
     * resource record set. Amazon Route 53 calculates the sum of the weights for the
     * resource record sets that have the same combination of DNS name and type. Amazon
     * Route 53 then responds to queries based on the ratio of a resource's weight to
     * the total. Note the following:</p> <ul> <li>You must specify a value for the
     * <code>Weight</code> element for every weighted resource record set.</li> <li>You
     * can only specify one <code>ResourceRecord</code> per weighted resource record
     * set.</li> <li>You cannot create latency, failover, or geolocation resource
     * record sets that have the same values for the <code>Name</code> and
     * <code>Type</code> elements as weighted resource record sets.</li> <li>You can
     * create a maximum of 100 weighted resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements.</li> <li><p>For
     * weighted (but not weighted alias) resource record sets, if you set
     * <code>Weight</code> to <code>0</code> for a resource record set, Amazon Route 53
     * never responds to queries with the applicable value for that resource record
     * set. However, if you set <code>Weight</code> to <code>0</code> for all resource
     * record sets that have the same combination of DNS name and type, traffic is
     * routed to all resources with equal probability.</p> <p>The effect of setting
     * <code>Weight</code> to <code>0</code> is different when you associate health
     * checks with weighted resource record sets. For more information, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/dns-failover-configuring-options.html">Options
     * for Configuring Amazon Route 53 Active-Active and Active-Passive Failover</a> in
     * the <i>Amazon Route 53 Developer Guide</i>.</p> </li> </ul>
     */
    inline ResourceRecordSet& WithWeight(long long value) { SetWeight(value); return *this;}

    /**
     * <p><i>Latency-based resource record sets only:</i> The Amazon EC2 region where
     * the resource that is specified in this resource record set resides. The resource
     * typically is an AWS resource, such as an Amazon EC2 instance or an ELB load
     * balancer, and is referred to by an IP address or a DNS domain name, depending on
     * the record type.</p> <note>You can create latency and latency alias resource
     * record sets only in public hosted zones.</note> <p>When Amazon Route 53 receives
     * a DNS query for a domain name and type for which you have created latency
     * resource record sets, Amazon Route 53 selects the latency resource record set
     * that has the lowest latency between the end user and the associated Amazon EC2
     * region. Amazon Route 53 then returns the value that is associated with the
     * selected resource record set.</p> <p>Note the following:</p> <ul> <li>You can
     * only specify one <code>ResourceRecord</code> per latency resource record
     * set.</li> <li>You can only create one latency resource record set for each
     * Amazon EC2 region.</li> <li>You are not required to create latency resource
     * record sets for all Amazon EC2 regions. Amazon Route 53 will choose the region
     * with the best latency from among the regions for which you create latency
     * resource record sets.</li> <li>You cannot create non-latency resource record
     * sets that have the same values for the <code>Name</code> and <code>Type</code>
     * elements as latency resource record sets.</li> </ul>
     */
    inline const ResourceRecordSetRegion& GetRegion() const{ return m_region; }

    /**
     * <p><i>Latency-based resource record sets only:</i> The Amazon EC2 region where
     * the resource that is specified in this resource record set resides. The resource
     * typically is an AWS resource, such as an Amazon EC2 instance or an ELB load
     * balancer, and is referred to by an IP address or a DNS domain name, depending on
     * the record type.</p> <note>You can create latency and latency alias resource
     * record sets only in public hosted zones.</note> <p>When Amazon Route 53 receives
     * a DNS query for a domain name and type for which you have created latency
     * resource record sets, Amazon Route 53 selects the latency resource record set
     * that has the lowest latency between the end user and the associated Amazon EC2
     * region. Amazon Route 53 then returns the value that is associated with the
     * selected resource record set.</p> <p>Note the following:</p> <ul> <li>You can
     * only specify one <code>ResourceRecord</code> per latency resource record
     * set.</li> <li>You can only create one latency resource record set for each
     * Amazon EC2 region.</li> <li>You are not required to create latency resource
     * record sets for all Amazon EC2 regions. Amazon Route 53 will choose the region
     * with the best latency from among the regions for which you create latency
     * resource record sets.</li> <li>You cannot create non-latency resource record
     * sets that have the same values for the <code>Name</code> and <code>Type</code>
     * elements as latency resource record sets.</li> </ul>
     */
    inline void SetRegion(const ResourceRecordSetRegion& value) { m_regionHasBeenSet = true; m_region = value; }

    /**
     * <p><i>Latency-based resource record sets only:</i> The Amazon EC2 region where
     * the resource that is specified in this resource record set resides. The resource
     * typically is an AWS resource, such as an Amazon EC2 instance or an ELB load
     * balancer, and is referred to by an IP address or a DNS domain name, depending on
     * the record type.</p> <note>You can create latency and latency alias resource
     * record sets only in public hosted zones.</note> <p>When Amazon Route 53 receives
     * a DNS query for a domain name and type for which you have created latency
     * resource record sets, Amazon Route 53 selects the latency resource record set
     * that has the lowest latency between the end user and the associated Amazon EC2
     * region. Amazon Route 53 then returns the value that is associated with the
     * selected resource record set.</p> <p>Note the following:</p> <ul> <li>You can
     * only specify one <code>ResourceRecord</code> per latency resource record
     * set.</li> <li>You can only create one latency resource record set for each
     * Amazon EC2 region.</li> <li>You are not required to create latency resource
     * record sets for all Amazon EC2 regions. Amazon Route 53 will choose the region
     * with the best latency from among the regions for which you create latency
     * resource record sets.</li> <li>You cannot create non-latency resource record
     * sets that have the same values for the <code>Name</code> and <code>Type</code>
     * elements as latency resource record sets.</li> </ul>
     */
    inline void SetRegion(ResourceRecordSetRegion&& value) { m_regionHasBeenSet = true; m_region = value; }

    /**
     * <p><i>Latency-based resource record sets only:</i> The Amazon EC2 region where
     * the resource that is specified in this resource record set resides. The resource
     * typically is an AWS resource, such as an Amazon EC2 instance or an ELB load
     * balancer, and is referred to by an IP address or a DNS domain name, depending on
     * the record type.</p> <note>You can create latency and latency alias resource
     * record sets only in public hosted zones.</note> <p>When Amazon Route 53 receives
     * a DNS query for a domain name and type for which you have created latency
     * resource record sets, Amazon Route 53 selects the latency resource record set
     * that has the lowest latency between the end user and the associated Amazon EC2
     * region. Amazon Route 53 then returns the value that is associated with the
     * selected resource record set.</p> <p>Note the following:</p> <ul> <li>You can
     * only specify one <code>ResourceRecord</code> per latency resource record
     * set.</li> <li>You can only create one latency resource record set for each
     * Amazon EC2 region.</li> <li>You are not required to create latency resource
     * record sets for all Amazon EC2 regions. Amazon Route 53 will choose the region
     * with the best latency from among the regions for which you create latency
     * resource record sets.</li> <li>You cannot create non-latency resource record
     * sets that have the same values for the <code>Name</code> and <code>Type</code>
     * elements as latency resource record sets.</li> </ul>
     */
    inline ResourceRecordSet& WithRegion(const ResourceRecordSetRegion& value) { SetRegion(value); return *this;}

    /**
     * <p><i>Latency-based resource record sets only:</i> The Amazon EC2 region where
     * the resource that is specified in this resource record set resides. The resource
     * typically is an AWS resource, such as an Amazon EC2 instance or an ELB load
     * balancer, and is referred to by an IP address or a DNS domain name, depending on
     * the record type.</p> <note>You can create latency and latency alias resource
     * record sets only in public hosted zones.</note> <p>When Amazon Route 53 receives
     * a DNS query for a domain name and type for which you have created latency
     * resource record sets, Amazon Route 53 selects the latency resource record set
     * that has the lowest latency between the end user and the associated Amazon EC2
     * region. Amazon Route 53 then returns the value that is associated with the
     * selected resource record set.</p> <p>Note the following:</p> <ul> <li>You can
     * only specify one <code>ResourceRecord</code> per latency resource record
     * set.</li> <li>You can only create one latency resource record set for each
     * Amazon EC2 region.</li> <li>You are not required to create latency resource
     * record sets for all Amazon EC2 regions. Amazon Route 53 will choose the region
     * with the best latency from among the regions for which you create latency
     * resource record sets.</li> <li>You cannot create non-latency resource record
     * sets that have the same values for the <code>Name</code> and <code>Type</code>
     * elements as latency resource record sets.</li> </ul>
     */
    inline ResourceRecordSet& WithRegion(ResourceRecordSetRegion&& value) { SetRegion(value); return *this;}

    /**
     * <p><i>Geo location resource record sets only:</i> A complex type that lets you
     * control how Amazon Route 53 responds to DNS queries based on the geographic
     * origin of the query. For example, if you want all queries from Africa to be
     * routed to a web server with an IP address of <code>192.0.2.111</code>, create a
     * resource record set with a <code>Type</code> of <code>A</code> and a
     * <code>ContinentCode</code> of <code>AF</code>.</p> <note>You can create
     * geolocation and geolocation alias resource record sets only in public hosted
     * zones.</note> <p>If you create separate resource record sets for overlapping
     * geographic regions (for example, one resource record set for a continent and one
     * for a country on the same continent), priority goes to the smallest geographic
     * region. This allows you to route most queries for a continent to one resource
     * and to route queries for a country on that continent to a different
     * resource.</p> <p>You cannot create two geolocation resource record sets that
     * specify the same geographic location.</p> <p>The value <code>*</code> in the
     * <code>CountryCode</code> element matches all geographic locations that aren't
     * specified in other geolocation resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements.</p>
     * <important>Geolocation works by mapping IP addresses to locations. However, some
     * IP addresses aren't mapped to geographic locations, so even if you create
     * geolocation resource record sets that cover all seven continents, Amazon Route
     * 53 will receive some DNS queries from locations that it can't identify. We
     * recommend that you create a resource record set for which the value of
     * <code>CountryCode</code> is <code>*</code>, which handles both queries that come
     * from locations for which you haven't created geolocation resource record sets
     * and queries from IP addresses that aren't mapped to a location. If you don't
     * create a <code>*</code> resource record set, Amazon Route 53 returns a "no
     * answer" response for queries from those locations.</important> <p>You cannot
     * create non-geolocation resource record sets that have the same values for the
     * <code>Name</code> and <code>Type</code> elements as geolocation resource record
     * sets.</p>
     */
    inline const GeoLocation& GetGeoLocation() const{ return m_geoLocation; }

    /**
     * <p><i>Geo location resource record sets only:</i> A complex type that lets you
     * control how Amazon Route 53 responds to DNS queries based on the geographic
     * origin of the query. For example, if you want all queries from Africa to be
     * routed to a web server with an IP address of <code>192.0.2.111</code>, create a
     * resource record set with a <code>Type</code> of <code>A</code> and a
     * <code>ContinentCode</code> of <code>AF</code>.</p> <note>You can create
     * geolocation and geolocation alias resource record sets only in public hosted
     * zones.</note> <p>If you create separate resource record sets for overlapping
     * geographic regions (for example, one resource record set for a continent and one
     * for a country on the same continent), priority goes to the smallest geographic
     * region. This allows you to route most queries for a continent to one resource
     * and to route queries for a country on that continent to a different
     * resource.</p> <p>You cannot create two geolocation resource record sets that
     * specify the same geographic location.</p> <p>The value <code>*</code> in the
     * <code>CountryCode</code> element matches all geographic locations that aren't
     * specified in other geolocation resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements.</p>
     * <important>Geolocation works by mapping IP addresses to locations. However, some
     * IP addresses aren't mapped to geographic locations, so even if you create
     * geolocation resource record sets that cover all seven continents, Amazon Route
     * 53 will receive some DNS queries from locations that it can't identify. We
     * recommend that you create a resource record set for which the value of
     * <code>CountryCode</code> is <code>*</code>, which handles both queries that come
     * from locations for which you haven't created geolocation resource record sets
     * and queries from IP addresses that aren't mapped to a location. If you don't
     * create a <code>*</code> resource record set, Amazon Route 53 returns a "no
     * answer" response for queries from those locations.</important> <p>You cannot
     * create non-geolocation resource record sets that have the same values for the
     * <code>Name</code> and <code>Type</code> elements as geolocation resource record
     * sets.</p>
     */
    inline void SetGeoLocation(const GeoLocation& value) { m_geoLocationHasBeenSet = true; m_geoLocation = value; }

    /**
     * <p><i>Geo location resource record sets only:</i> A complex type that lets you
     * control how Amazon Route 53 responds to DNS queries based on the geographic
     * origin of the query. For example, if you want all queries from Africa to be
     * routed to a web server with an IP address of <code>192.0.2.111</code>, create a
     * resource record set with a <code>Type</code> of <code>A</code> and a
     * <code>ContinentCode</code> of <code>AF</code>.</p> <note>You can create
     * geolocation and geolocation alias resource record sets only in public hosted
     * zones.</note> <p>If you create separate resource record sets for overlapping
     * geographic regions (for example, one resource record set for a continent and one
     * for a country on the same continent), priority goes to the smallest geographic
     * region. This allows you to route most queries for a continent to one resource
     * and to route queries for a country on that continent to a different
     * resource.</p> <p>You cannot create two geolocation resource record sets that
     * specify the same geographic location.</p> <p>The value <code>*</code> in the
     * <code>CountryCode</code> element matches all geographic locations that aren't
     * specified in other geolocation resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements.</p>
     * <important>Geolocation works by mapping IP addresses to locations. However, some
     * IP addresses aren't mapped to geographic locations, so even if you create
     * geolocation resource record sets that cover all seven continents, Amazon Route
     * 53 will receive some DNS queries from locations that it can't identify. We
     * recommend that you create a resource record set for which the value of
     * <code>CountryCode</code> is <code>*</code>, which handles both queries that come
     * from locations for which you haven't created geolocation resource record sets
     * and queries from IP addresses that aren't mapped to a location. If you don't
     * create a <code>*</code> resource record set, Amazon Route 53 returns a "no
     * answer" response for queries from those locations.</important> <p>You cannot
     * create non-geolocation resource record sets that have the same values for the
     * <code>Name</code> and <code>Type</code> elements as geolocation resource record
     * sets.</p>
     */
    inline void SetGeoLocation(GeoLocation&& value) { m_geoLocationHasBeenSet = true; m_geoLocation = value; }

    /**
     * <p><i>Geo location resource record sets only:</i> A complex type that lets you
     * control how Amazon Route 53 responds to DNS queries based on the geographic
     * origin of the query. For example, if you want all queries from Africa to be
     * routed to a web server with an IP address of <code>192.0.2.111</code>, create a
     * resource record set with a <code>Type</code> of <code>A</code> and a
     * <code>ContinentCode</code> of <code>AF</code>.</p> <note>You can create
     * geolocation and geolocation alias resource record sets only in public hosted
     * zones.</note> <p>If you create separate resource record sets for overlapping
     * geographic regions (for example, one resource record set for a continent and one
     * for a country on the same continent), priority goes to the smallest geographic
     * region. This allows you to route most queries for a continent to one resource
     * and to route queries for a country on that continent to a different
     * resource.</p> <p>You cannot create two geolocation resource record sets that
     * specify the same geographic location.</p> <p>The value <code>*</code> in the
     * <code>CountryCode</code> element matches all geographic locations that aren't
     * specified in other geolocation resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements.</p>
     * <important>Geolocation works by mapping IP addresses to locations. However, some
     * IP addresses aren't mapped to geographic locations, so even if you create
     * geolocation resource record sets that cover all seven continents, Amazon Route
     * 53 will receive some DNS queries from locations that it can't identify. We
     * recommend that you create a resource record set for which the value of
     * <code>CountryCode</code> is <code>*</code>, which handles both queries that come
     * from locations for which you haven't created geolocation resource record sets
     * and queries from IP addresses that aren't mapped to a location. If you don't
     * create a <code>*</code> resource record set, Amazon Route 53 returns a "no
     * answer" response for queries from those locations.</important> <p>You cannot
     * create non-geolocation resource record sets that have the same values for the
     * <code>Name</code> and <code>Type</code> elements as geolocation resource record
     * sets.</p>
     */
    inline ResourceRecordSet& WithGeoLocation(const GeoLocation& value) { SetGeoLocation(value); return *this;}

    /**
     * <p><i>Geo location resource record sets only:</i> A complex type that lets you
     * control how Amazon Route 53 responds to DNS queries based on the geographic
     * origin of the query. For example, if you want all queries from Africa to be
     * routed to a web server with an IP address of <code>192.0.2.111</code>, create a
     * resource record set with a <code>Type</code> of <code>A</code> and a
     * <code>ContinentCode</code> of <code>AF</code>.</p> <note>You can create
     * geolocation and geolocation alias resource record sets only in public hosted
     * zones.</note> <p>If you create separate resource record sets for overlapping
     * geographic regions (for example, one resource record set for a continent and one
     * for a country on the same continent), priority goes to the smallest geographic
     * region. This allows you to route most queries for a continent to one resource
     * and to route queries for a country on that continent to a different
     * resource.</p> <p>You cannot create two geolocation resource record sets that
     * specify the same geographic location.</p> <p>The value <code>*</code> in the
     * <code>CountryCode</code> element matches all geographic locations that aren't
     * specified in other geolocation resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements.</p>
     * <important>Geolocation works by mapping IP addresses to locations. However, some
     * IP addresses aren't mapped to geographic locations, so even if you create
     * geolocation resource record sets that cover all seven continents, Amazon Route
     * 53 will receive some DNS queries from locations that it can't identify. We
     * recommend that you create a resource record set for which the value of
     * <code>CountryCode</code> is <code>*</code>, which handles both queries that come
     * from locations for which you haven't created geolocation resource record sets
     * and queries from IP addresses that aren't mapped to a location. If you don't
     * create a <code>*</code> resource record set, Amazon Route 53 returns a "no
     * answer" response for queries from those locations.</important> <p>You cannot
     * create non-geolocation resource record sets that have the same values for the
     * <code>Name</code> and <code>Type</code> elements as geolocation resource record
     * sets.</p>
     */
    inline ResourceRecordSet& WithGeoLocation(GeoLocation&& value) { SetGeoLocation(value); return *this;}

    /**
     * <p><i>Failover resource record sets only:</i> To configure failover, you add the
     * <code>Failover</code> element to two resource record sets. For one resource
     * record set, you specify <code>PRIMARY</code> as the value for
     * <code>Failover</code>; for the other resource record set, you specify
     * <code>SECONDARY</code>. In addition, you include the <code>HealthCheckId</code>
     * element and specify the health check that you want Amazon Route 53 to perform
     * for each resource record set.</p> <note>You can create failover and failover
     * alias resource record sets only in public hosted zones.</note> <p>Except where
     * noted, the following failover behaviors assume that you have included the
     * <code>HealthCheckId</code> element in both resource record sets:</p> <ul>
     * <li>When the primary resource record set is healthy, Amazon Route 53 responds to
     * DNS queries with the applicable value from the primary resource record set
     * regardless of the health of the secondary resource record set.</li> <li>When the
     * primary resource record set is unhealthy and the secondary resource record set
     * is healthy, Amazon Route 53 responds to DNS queries with the applicable value
     * from the secondary resource record set.</li> <li>When the secondary resource
     * record set is unhealthy, Amazon Route 53 responds to DNS queries with the
     * applicable value from the primary resource record set regardless of the health
     * of the primary resource record set.</li> <li>If you omit the
     * <code>HealthCheckId</code> element for the secondary resource record set, and if
     * the primary resource record set is unhealthy, Amazon Route 53 always responds to
     * DNS queries with the applicable value from the secondary resource record set.
     * This is true regardless of the health of the associated endpoint.</li> </ul>
     * <p>You cannot create non-failover resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements as failover resource
     * record sets.</p> <p>For failover alias resource record sets, you must also
     * include the <code>EvaluateTargetHealth</code> element and set the value to
     * true.</p> <p>For more information about configuring failover for Amazon Route
     * 53, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/dns-failover.html">Amazon
     * Route 53 Health Checks and DNS Failover</a> in the <i>Amazon Route 53 Developer
     * Guide</i>.</p> <p>Valid values: <code>PRIMARY</code> |
     * <code>SECONDARY</code></p>
     */
    inline const ResourceRecordSetFailover& GetFailover() const{ return m_failover; }

    /**
     * <p><i>Failover resource record sets only:</i> To configure failover, you add the
     * <code>Failover</code> element to two resource record sets. For one resource
     * record set, you specify <code>PRIMARY</code> as the value for
     * <code>Failover</code>; for the other resource record set, you specify
     * <code>SECONDARY</code>. In addition, you include the <code>HealthCheckId</code>
     * element and specify the health check that you want Amazon Route 53 to perform
     * for each resource record set.</p> <note>You can create failover and failover
     * alias resource record sets only in public hosted zones.</note> <p>Except where
     * noted, the following failover behaviors assume that you have included the
     * <code>HealthCheckId</code> element in both resource record sets:</p> <ul>
     * <li>When the primary resource record set is healthy, Amazon Route 53 responds to
     * DNS queries with the applicable value from the primary resource record set
     * regardless of the health of the secondary resource record set.</li> <li>When the
     * primary resource record set is unhealthy and the secondary resource record set
     * is healthy, Amazon Route 53 responds to DNS queries with the applicable value
     * from the secondary resource record set.</li> <li>When the secondary resource
     * record set is unhealthy, Amazon Route 53 responds to DNS queries with the
     * applicable value from the primary resource record set regardless of the health
     * of the primary resource record set.</li> <li>If you omit the
     * <code>HealthCheckId</code> element for the secondary resource record set, and if
     * the primary resource record set is unhealthy, Amazon Route 53 always responds to
     * DNS queries with the applicable value from the secondary resource record set.
     * This is true regardless of the health of the associated endpoint.</li> </ul>
     * <p>You cannot create non-failover resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements as failover resource
     * record sets.</p> <p>For failover alias resource record sets, you must also
     * include the <code>EvaluateTargetHealth</code> element and set the value to
     * true.</p> <p>For more information about configuring failover for Amazon Route
     * 53, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/dns-failover.html">Amazon
     * Route 53 Health Checks and DNS Failover</a> in the <i>Amazon Route 53 Developer
     * Guide</i>.</p> <p>Valid values: <code>PRIMARY</code> |
     * <code>SECONDARY</code></p>
     */
    inline void SetFailover(const ResourceRecordSetFailover& value) { m_failoverHasBeenSet = true; m_failover = value; }

    /**
     * <p><i>Failover resource record sets only:</i> To configure failover, you add the
     * <code>Failover</code> element to two resource record sets. For one resource
     * record set, you specify <code>PRIMARY</code> as the value for
     * <code>Failover</code>; for the other resource record set, you specify
     * <code>SECONDARY</code>. In addition, you include the <code>HealthCheckId</code>
     * element and specify the health check that you want Amazon Route 53 to perform
     * for each resource record set.</p> <note>You can create failover and failover
     * alias resource record sets only in public hosted zones.</note> <p>Except where
     * noted, the following failover behaviors assume that you have included the
     * <code>HealthCheckId</code> element in both resource record sets:</p> <ul>
     * <li>When the primary resource record set is healthy, Amazon Route 53 responds to
     * DNS queries with the applicable value from the primary resource record set
     * regardless of the health of the secondary resource record set.</li> <li>When the
     * primary resource record set is unhealthy and the secondary resource record set
     * is healthy, Amazon Route 53 responds to DNS queries with the applicable value
     * from the secondary resource record set.</li> <li>When the secondary resource
     * record set is unhealthy, Amazon Route 53 responds to DNS queries with the
     * applicable value from the primary resource record set regardless of the health
     * of the primary resource record set.</li> <li>If you omit the
     * <code>HealthCheckId</code> element for the secondary resource record set, and if
     * the primary resource record set is unhealthy, Amazon Route 53 always responds to
     * DNS queries with the applicable value from the secondary resource record set.
     * This is true regardless of the health of the associated endpoint.</li> </ul>
     * <p>You cannot create non-failover resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements as failover resource
     * record sets.</p> <p>For failover alias resource record sets, you must also
     * include the <code>EvaluateTargetHealth</code> element and set the value to
     * true.</p> <p>For more information about configuring failover for Amazon Route
     * 53, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/dns-failover.html">Amazon
     * Route 53 Health Checks and DNS Failover</a> in the <i>Amazon Route 53 Developer
     * Guide</i>.</p> <p>Valid values: <code>PRIMARY</code> |
     * <code>SECONDARY</code></p>
     */
    inline void SetFailover(ResourceRecordSetFailover&& value) { m_failoverHasBeenSet = true; m_failover = value; }

    /**
     * <p><i>Failover resource record sets only:</i> To configure failover, you add the
     * <code>Failover</code> element to two resource record sets. For one resource
     * record set, you specify <code>PRIMARY</code> as the value for
     * <code>Failover</code>; for the other resource record set, you specify
     * <code>SECONDARY</code>. In addition, you include the <code>HealthCheckId</code>
     * element and specify the health check that you want Amazon Route 53 to perform
     * for each resource record set.</p> <note>You can create failover and failover
     * alias resource record sets only in public hosted zones.</note> <p>Except where
     * noted, the following failover behaviors assume that you have included the
     * <code>HealthCheckId</code> element in both resource record sets:</p> <ul>
     * <li>When the primary resource record set is healthy, Amazon Route 53 responds to
     * DNS queries with the applicable value from the primary resource record set
     * regardless of the health of the secondary resource record set.</li> <li>When the
     * primary resource record set is unhealthy and the secondary resource record set
     * is healthy, Amazon Route 53 responds to DNS queries with the applicable value
     * from the secondary resource record set.</li> <li>When the secondary resource
     * record set is unhealthy, Amazon Route 53 responds to DNS queries with the
     * applicable value from the primary resource record set regardless of the health
     * of the primary resource record set.</li> <li>If you omit the
     * <code>HealthCheckId</code> element for the secondary resource record set, and if
     * the primary resource record set is unhealthy, Amazon Route 53 always responds to
     * DNS queries with the applicable value from the secondary resource record set.
     * This is true regardless of the health of the associated endpoint.</li> </ul>
     * <p>You cannot create non-failover resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements as failover resource
     * record sets.</p> <p>For failover alias resource record sets, you must also
     * include the <code>EvaluateTargetHealth</code> element and set the value to
     * true.</p> <p>For more information about configuring failover for Amazon Route
     * 53, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/dns-failover.html">Amazon
     * Route 53 Health Checks and DNS Failover</a> in the <i>Amazon Route 53 Developer
     * Guide</i>.</p> <p>Valid values: <code>PRIMARY</code> |
     * <code>SECONDARY</code></p>
     */
    inline ResourceRecordSet& WithFailover(const ResourceRecordSetFailover& value) { SetFailover(value); return *this;}

    /**
     * <p><i>Failover resource record sets only:</i> To configure failover, you add the
     * <code>Failover</code> element to two resource record sets. For one resource
     * record set, you specify <code>PRIMARY</code> as the value for
     * <code>Failover</code>; for the other resource record set, you specify
     * <code>SECONDARY</code>. In addition, you include the <code>HealthCheckId</code>
     * element and specify the health check that you want Amazon Route 53 to perform
     * for each resource record set.</p> <note>You can create failover and failover
     * alias resource record sets only in public hosted zones.</note> <p>Except where
     * noted, the following failover behaviors assume that you have included the
     * <code>HealthCheckId</code> element in both resource record sets:</p> <ul>
     * <li>When the primary resource record set is healthy, Amazon Route 53 responds to
     * DNS queries with the applicable value from the primary resource record set
     * regardless of the health of the secondary resource record set.</li> <li>When the
     * primary resource record set is unhealthy and the secondary resource record set
     * is healthy, Amazon Route 53 responds to DNS queries with the applicable value
     * from the secondary resource record set.</li> <li>When the secondary resource
     * record set is unhealthy, Amazon Route 53 responds to DNS queries with the
     * applicable value from the primary resource record set regardless of the health
     * of the primary resource record set.</li> <li>If you omit the
     * <code>HealthCheckId</code> element for the secondary resource record set, and if
     * the primary resource record set is unhealthy, Amazon Route 53 always responds to
     * DNS queries with the applicable value from the secondary resource record set.
     * This is true regardless of the health of the associated endpoint.</li> </ul>
     * <p>You cannot create non-failover resource record sets that have the same values
     * for the <code>Name</code> and <code>Type</code> elements as failover resource
     * record sets.</p> <p>For failover alias resource record sets, you must also
     * include the <code>EvaluateTargetHealth</code> element and set the value to
     * true.</p> <p>For more information about configuring failover for Amazon Route
     * 53, see <a
     * href="http://docs.aws.amazon.com/Route53/latest/DeveloperGuide/dns-failover.html">Amazon
     * Route 53 Health Checks and DNS Failover</a> in the <i>Amazon Route 53 Developer
     * Guide</i>.</p> <p>Valid values: <code>PRIMARY</code> |
     * <code>SECONDARY</code></p>
     */
    inline ResourceRecordSet& WithFailover(ResourceRecordSetFailover&& value) { SetFailover(value); return *this;}

    /**
     * <p>The cache time to live for the current resource record set. Note the
     * following:</p> <ul> <li>If you're creating a non-alias resource record set,
     * <code>TTL</code> is required. </li> <li>If you're creating an alias resource
     * record set, omit <code>TTL</code>. Amazon Route 53 uses the value of
     * <code>TTL</code> for the alias target. </li> <li>If you're associating this
     * resource record set with a health check (if you're adding a
     * <code>HealthCheckId</code> element), we recommend that you specify a
     * <code>TTL</code> of 60 seconds or less so clients respond quickly to changes in
     * health status.</li> <li>All of the resource record sets in a group of weighted,
     * latency, geolocation, or failover resource record sets must have the same value
     * for <code>TTL</code>.</li> <li>If a group of weighted resource record sets
     * includes one or more weighted alias resource record sets for which the alias
     * target is an ELB load balancer, we recommend that you specify a <code>TTL</code>
     * of 60 seconds for all of the non-alias weighted resource record sets that have
     * the same name and type. Values other than 60 seconds (the TTL for load
     * balancers) will change the effect of the values that you specify for
     * <code>Weight</code>.</li> </ul>
     */
    inline long long GetTTL() const{ return m_tTL; }

    /**
     * <p>The cache time to live for the current resource record set. Note the
     * following:</p> <ul> <li>If you're creating a non-alias resource record set,
     * <code>TTL</code> is required. </li> <li>If you're creating an alias resource
     * record set, omit <code>TTL</code>. Amazon Route 53 uses the value of
     * <code>TTL</code> for the alias target. </li> <li>If you're associating this
     * resource record set with a health check (if you're adding a
     * <code>HealthCheckId</code> element), we recommend that you specify a
     * <code>TTL</code> of 60 seconds or less so clients respond quickly to changes in
     * health status.</li> <li>All of the resource record sets in a group of weighted,
     * latency, geolocation, or failover resource record sets must have the same value
     * for <code>TTL</code>.</li> <li>If a group of weighted resource record sets
     * includes one or more weighted alias resource record sets for which the alias
     * target is an ELB load balancer, we recommend that you specify a <code>TTL</code>
     * of 60 seconds for all of the non-alias weighted resource record sets that have
     * the same name and type. Values other than 60 seconds (the TTL for load
     * balancers) will change the effect of the values that you specify for
     * <code>Weight</code>.</li> </ul>
     */
    inline void SetTTL(long long value) { m_tTLHasBeenSet = true; m_tTL = value; }

    /**
     * <p>The cache time to live for the current resource record set. Note the
     * following:</p> <ul> <li>If you're creating a non-alias resource record set,
     * <code>TTL</code> is required. </li> <li>If you're creating an alias resource
     * record set, omit <code>TTL</code>. Amazon Route 53 uses the value of
     * <code>TTL</code> for the alias target. </li> <li>If you're associating this
     * resource record set with a health check (if you're adding a
     * <code>HealthCheckId</code> element), we recommend that you specify a
     * <code>TTL</code> of 60 seconds or less so clients respond quickly to changes in
     * health status.</li> <li>All of the resource record sets in a group of weighted,
     * latency, geolocation, or failover resource record sets must have the same value
     * for <code>TTL</code>.</li> <li>If a group of weighted resource record sets
     * includes one or more weighted alias resource record sets for which the alias
     * target is an ELB load balancer, we recommend that you specify a <code>TTL</code>
     * of 60 seconds for all of the non-alias weighted resource record sets that have
     * the same name and type. Values other than 60 seconds (the TTL for load
     * balancers) will change the effect of the values that you specify for
     * <code>Weight</code>.</li> </ul>
     */
    inline ResourceRecordSet& WithTTL(long long value) { SetTTL(value); return *this;}

    /**
     * <p>A complex type that contains the resource records for the current resource
     * record set.</p>
     */
    inline const Aws::Vector<ResourceRecord>& GetResourceRecords() const{ return m_resourceRecords; }

    /**
     * <p>A complex type that contains the resource records for the current resource
     * record set.</p>
     */
    inline void SetResourceRecords(const Aws::Vector<ResourceRecord>& value) { m_resourceRecordsHasBeenSet = true; m_resourceRecords = value; }

    /**
     * <p>A complex type that contains the resource records for the current resource
     * record set.</p>
     */
    inline void SetResourceRecords(Aws::Vector<ResourceRecord>&& value) { m_resourceRecordsHasBeenSet = true; m_resourceRecords = value; }

    /**
     * <p>A complex type that contains the resource records for the current resource
     * record set.</p>
     */
    inline ResourceRecordSet& WithResourceRecords(const Aws::Vector<ResourceRecord>& value) { SetResourceRecords(value); return *this;}

    /**
     * <p>A complex type that contains the resource records for the current resource
     * record set.</p>
     */
    inline ResourceRecordSet& WithResourceRecords(Aws::Vector<ResourceRecord>&& value) { SetResourceRecords(value); return *this;}

    /**
     * <p>A complex type that contains the resource records for the current resource
     * record set.</p>
     */
    inline ResourceRecordSet& AddResourceRecords(const ResourceRecord& value) { m_resourceRecordsHasBeenSet = true; m_resourceRecords.push_back(value); return *this; }

    /**
     * <p>A complex type that contains the resource records for the current resource
     * record set.</p>
     */
    inline ResourceRecordSet& AddResourceRecords(ResourceRecord&& value) { m_resourceRecordsHasBeenSet = true; m_resourceRecords.push_back(value); return *this; }

    /**
     * <p><i>Alias resource record sets only:</i> Information about the AWS resource to
     * which you are redirecting traffic.</p>
     */
    inline const AliasTarget& GetAliasTarget() const{ return m_aliasTarget; }

    /**
     * <p><i>Alias resource record sets only:</i> Information about the AWS resource to
     * which you are redirecting traffic.</p>
     */
    inline void SetAliasTarget(const AliasTarget& value) { m_aliasTargetHasBeenSet = true; m_aliasTarget = value; }

    /**
     * <p><i>Alias resource record sets only:</i> Information about the AWS resource to
     * which you are redirecting traffic.</p>
     */
    inline void SetAliasTarget(AliasTarget&& value) { m_aliasTargetHasBeenSet = true; m_aliasTarget = value; }

    /**
     * <p><i>Alias resource record sets only:</i> Information about the AWS resource to
     * which you are redirecting traffic.</p>
     */
    inline ResourceRecordSet& WithAliasTarget(const AliasTarget& value) { SetAliasTarget(value); return *this;}

    /**
     * <p><i>Alias resource record sets only:</i> Information about the AWS resource to
     * which you are redirecting traffic.</p>
     */
    inline ResourceRecordSet& WithAliasTarget(AliasTarget&& value) { SetAliasTarget(value); return *this;}

    /**
     * <p><i>Health Check resource record sets only, not required for alias resource
     * record sets:</i> An identifier that is used to identify health check associated
     * with the resource record set.</p>
     */
    inline const Aws::String& GetHealthCheckId() const{ return m_healthCheckId; }

    /**
     * <p><i>Health Check resource record sets only, not required for alias resource
     * record sets:</i> An identifier that is used to identify health check associated
     * with the resource record set.</p>
     */
    inline void SetHealthCheckId(const Aws::String& value) { m_healthCheckIdHasBeenSet = true; m_healthCheckId = value; }

    /**
     * <p><i>Health Check resource record sets only, not required for alias resource
     * record sets:</i> An identifier that is used to identify health check associated
     * with the resource record set.</p>
     */
    inline void SetHealthCheckId(Aws::String&& value) { m_healthCheckIdHasBeenSet = true; m_healthCheckId = value; }

    /**
     * <p><i>Health Check resource record sets only, not required for alias resource
     * record sets:</i> An identifier that is used to identify health check associated
     * with the resource record set.</p>
     */
    inline void SetHealthCheckId(const char* value) { m_healthCheckIdHasBeenSet = true; m_healthCheckId.assign(value); }

    /**
     * <p><i>Health Check resource record sets only, not required for alias resource
     * record sets:</i> An identifier that is used to identify health check associated
     * with the resource record set.</p>
     */
    inline ResourceRecordSet& WithHealthCheckId(const Aws::String& value) { SetHealthCheckId(value); return *this;}

    /**
     * <p><i>Health Check resource record sets only, not required for alias resource
     * record sets:</i> An identifier that is used to identify health check associated
     * with the resource record set.</p>
     */
    inline ResourceRecordSet& WithHealthCheckId(Aws::String&& value) { SetHealthCheckId(value); return *this;}

    /**
     * <p><i>Health Check resource record sets only, not required for alias resource
     * record sets:</i> An identifier that is used to identify health check associated
     * with the resource record set.</p>
     */
    inline ResourceRecordSet& WithHealthCheckId(const char* value) { SetHealthCheckId(value); return *this;}

    
    inline const Aws::String& GetTrafficPolicyInstanceId() const{ return m_trafficPolicyInstanceId; }

    
    inline void SetTrafficPolicyInstanceId(const Aws::String& value) { m_trafficPolicyInstanceIdHasBeenSet = true; m_trafficPolicyInstanceId = value; }

    
    inline void SetTrafficPolicyInstanceId(Aws::String&& value) { m_trafficPolicyInstanceIdHasBeenSet = true; m_trafficPolicyInstanceId = value; }

    
    inline void SetTrafficPolicyInstanceId(const char* value) { m_trafficPolicyInstanceIdHasBeenSet = true; m_trafficPolicyInstanceId.assign(value); }

    
    inline ResourceRecordSet& WithTrafficPolicyInstanceId(const Aws::String& value) { SetTrafficPolicyInstanceId(value); return *this;}

    
    inline ResourceRecordSet& WithTrafficPolicyInstanceId(Aws::String&& value) { SetTrafficPolicyInstanceId(value); return *this;}

    
    inline ResourceRecordSet& WithTrafficPolicyInstanceId(const char* value) { SetTrafficPolicyInstanceId(value); return *this;}

  private:
    Aws::String m_name;
    bool m_nameHasBeenSet;
    RRType m_type;
    bool m_typeHasBeenSet;
    Aws::String m_setIdentifier;
    bool m_setIdentifierHasBeenSet;
    long long m_weight;
    bool m_weightHasBeenSet;
    ResourceRecordSetRegion m_region;
    bool m_regionHasBeenSet;
    GeoLocation m_geoLocation;
    bool m_geoLocationHasBeenSet;
    ResourceRecordSetFailover m_failover;
    bool m_failoverHasBeenSet;
    long long m_tTL;
    bool m_tTLHasBeenSet;
    Aws::Vector<ResourceRecord> m_resourceRecords;
    bool m_resourceRecordsHasBeenSet;
    AliasTarget m_aliasTarget;
    bool m_aliasTargetHasBeenSet;
    Aws::String m_healthCheckId;
    bool m_healthCheckIdHasBeenSet;
    Aws::String m_trafficPolicyInstanceId;
    bool m_trafficPolicyInstanceIdHasBeenSet;
  };

} // namespace Model
} // namespace Route53
} // namespace Aws
