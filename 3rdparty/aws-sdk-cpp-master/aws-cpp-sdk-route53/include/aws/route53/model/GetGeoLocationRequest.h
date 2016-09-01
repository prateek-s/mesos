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

namespace Aws
{
namespace Http
{
    class URI;
} //namespace Http
namespace Route53
{
namespace Model
{

  /**
   * <p>A complex type that contains information about the request to get a geo
   * location.</p>
   */
  class AWS_ROUTE53_API GetGeoLocationRequest : public Route53Request
  {
  public:
    GetGeoLocationRequest();
    Aws::String SerializePayload() const override;

    void AddQueryStringParameters(Aws::Http::URI& uri) const override;

    /**
     * <p>The code for a continent geo location. Note: only continent locations have a
     * continent code.</p> <p>Valid values: <code>AF</code> | <code>AN</code> |
     * <code>AS</code> | <code>EU</code> | <code>OC</code> | <code>NA</code> |
     * <code>SA</code></p> <p>Constraint: Specifying <code>ContinentCode</code> with
     * either <code>CountryCode</code> or <code>SubdivisionCode</code> returns an
     * <code>InvalidInput</code> error.</p>
     */
    inline const Aws::String& GetContinentCode() const{ return m_continentCode; }

    /**
     * <p>The code for a continent geo location. Note: only continent locations have a
     * continent code.</p> <p>Valid values: <code>AF</code> | <code>AN</code> |
     * <code>AS</code> | <code>EU</code> | <code>OC</code> | <code>NA</code> |
     * <code>SA</code></p> <p>Constraint: Specifying <code>ContinentCode</code> with
     * either <code>CountryCode</code> or <code>SubdivisionCode</code> returns an
     * <code>InvalidInput</code> error.</p>
     */
    inline void SetContinentCode(const Aws::String& value) { m_continentCodeHasBeenSet = true; m_continentCode = value; }

    /**
     * <p>The code for a continent geo location. Note: only continent locations have a
     * continent code.</p> <p>Valid values: <code>AF</code> | <code>AN</code> |
     * <code>AS</code> | <code>EU</code> | <code>OC</code> | <code>NA</code> |
     * <code>SA</code></p> <p>Constraint: Specifying <code>ContinentCode</code> with
     * either <code>CountryCode</code> or <code>SubdivisionCode</code> returns an
     * <code>InvalidInput</code> error.</p>
     */
    inline void SetContinentCode(Aws::String&& value) { m_continentCodeHasBeenSet = true; m_continentCode = value; }

    /**
     * <p>The code for a continent geo location. Note: only continent locations have a
     * continent code.</p> <p>Valid values: <code>AF</code> | <code>AN</code> |
     * <code>AS</code> | <code>EU</code> | <code>OC</code> | <code>NA</code> |
     * <code>SA</code></p> <p>Constraint: Specifying <code>ContinentCode</code> with
     * either <code>CountryCode</code> or <code>SubdivisionCode</code> returns an
     * <code>InvalidInput</code> error.</p>
     */
    inline void SetContinentCode(const char* value) { m_continentCodeHasBeenSet = true; m_continentCode.assign(value); }

    /**
     * <p>The code for a continent geo location. Note: only continent locations have a
     * continent code.</p> <p>Valid values: <code>AF</code> | <code>AN</code> |
     * <code>AS</code> | <code>EU</code> | <code>OC</code> | <code>NA</code> |
     * <code>SA</code></p> <p>Constraint: Specifying <code>ContinentCode</code> with
     * either <code>CountryCode</code> or <code>SubdivisionCode</code> returns an
     * <code>InvalidInput</code> error.</p>
     */
    inline GetGeoLocationRequest& WithContinentCode(const Aws::String& value) { SetContinentCode(value); return *this;}

    /**
     * <p>The code for a continent geo location. Note: only continent locations have a
     * continent code.</p> <p>Valid values: <code>AF</code> | <code>AN</code> |
     * <code>AS</code> | <code>EU</code> | <code>OC</code> | <code>NA</code> |
     * <code>SA</code></p> <p>Constraint: Specifying <code>ContinentCode</code> with
     * either <code>CountryCode</code> or <code>SubdivisionCode</code> returns an
     * <code>InvalidInput</code> error.</p>
     */
    inline GetGeoLocationRequest& WithContinentCode(Aws::String&& value) { SetContinentCode(value); return *this;}

    /**
     * <p>The code for a continent geo location. Note: only continent locations have a
     * continent code.</p> <p>Valid values: <code>AF</code> | <code>AN</code> |
     * <code>AS</code> | <code>EU</code> | <code>OC</code> | <code>NA</code> |
     * <code>SA</code></p> <p>Constraint: Specifying <code>ContinentCode</code> with
     * either <code>CountryCode</code> or <code>SubdivisionCode</code> returns an
     * <code>InvalidInput</code> error.</p>
     */
    inline GetGeoLocationRequest& WithContinentCode(const char* value) { SetContinentCode(value); return *this;}

    /**
     * <p>The code for a country geo location. The default location uses '*' for the
     * country code and will match all locations that are not matched by a geo
     * location.</p> <p>The default geo location uses a <code>*</code> for the country
     * code. All other country codes follow the ISO 3166 two-character code.</p>
     */
    inline const Aws::String& GetCountryCode() const{ return m_countryCode; }

    /**
     * <p>The code for a country geo location. The default location uses '*' for the
     * country code and will match all locations that are not matched by a geo
     * location.</p> <p>The default geo location uses a <code>*</code> for the country
     * code. All other country codes follow the ISO 3166 two-character code.</p>
     */
    inline void SetCountryCode(const Aws::String& value) { m_countryCodeHasBeenSet = true; m_countryCode = value; }

    /**
     * <p>The code for a country geo location. The default location uses '*' for the
     * country code and will match all locations that are not matched by a geo
     * location.</p> <p>The default geo location uses a <code>*</code> for the country
     * code. All other country codes follow the ISO 3166 two-character code.</p>
     */
    inline void SetCountryCode(Aws::String&& value) { m_countryCodeHasBeenSet = true; m_countryCode = value; }

    /**
     * <p>The code for a country geo location. The default location uses '*' for the
     * country code and will match all locations that are not matched by a geo
     * location.</p> <p>The default geo location uses a <code>*</code> for the country
     * code. All other country codes follow the ISO 3166 two-character code.</p>
     */
    inline void SetCountryCode(const char* value) { m_countryCodeHasBeenSet = true; m_countryCode.assign(value); }

    /**
     * <p>The code for a country geo location. The default location uses '*' for the
     * country code and will match all locations that are not matched by a geo
     * location.</p> <p>The default geo location uses a <code>*</code> for the country
     * code. All other country codes follow the ISO 3166 two-character code.</p>
     */
    inline GetGeoLocationRequest& WithCountryCode(const Aws::String& value) { SetCountryCode(value); return *this;}

    /**
     * <p>The code for a country geo location. The default location uses '*' for the
     * country code and will match all locations that are not matched by a geo
     * location.</p> <p>The default geo location uses a <code>*</code> for the country
     * code. All other country codes follow the ISO 3166 two-character code.</p>
     */
    inline GetGeoLocationRequest& WithCountryCode(Aws::String&& value) { SetCountryCode(value); return *this;}

    /**
     * <p>The code for a country geo location. The default location uses '*' for the
     * country code and will match all locations that are not matched by a geo
     * location.</p> <p>The default geo location uses a <code>*</code> for the country
     * code. All other country codes follow the ISO 3166 two-character code.</p>
     */
    inline GetGeoLocationRequest& WithCountryCode(const char* value) { SetCountryCode(value); return *this;}

    /**
     * <p>The code for a country's subdivision (e.g., a province of Canada). A
     * subdivision code is only valid with the appropriate country code.</p>
     * <p>Constraint: Specifying <code>SubdivisionCode</code> without
     * <code>CountryCode</code> returns an <code>InvalidInput</code> error.</p>
     */
    inline const Aws::String& GetSubdivisionCode() const{ return m_subdivisionCode; }

    /**
     * <p>The code for a country's subdivision (e.g., a province of Canada). A
     * subdivision code is only valid with the appropriate country code.</p>
     * <p>Constraint: Specifying <code>SubdivisionCode</code> without
     * <code>CountryCode</code> returns an <code>InvalidInput</code> error.</p>
     */
    inline void SetSubdivisionCode(const Aws::String& value) { m_subdivisionCodeHasBeenSet = true; m_subdivisionCode = value; }

    /**
     * <p>The code for a country's subdivision (e.g., a province of Canada). A
     * subdivision code is only valid with the appropriate country code.</p>
     * <p>Constraint: Specifying <code>SubdivisionCode</code> without
     * <code>CountryCode</code> returns an <code>InvalidInput</code> error.</p>
     */
    inline void SetSubdivisionCode(Aws::String&& value) { m_subdivisionCodeHasBeenSet = true; m_subdivisionCode = value; }

    /**
     * <p>The code for a country's subdivision (e.g., a province of Canada). A
     * subdivision code is only valid with the appropriate country code.</p>
     * <p>Constraint: Specifying <code>SubdivisionCode</code> without
     * <code>CountryCode</code> returns an <code>InvalidInput</code> error.</p>
     */
    inline void SetSubdivisionCode(const char* value) { m_subdivisionCodeHasBeenSet = true; m_subdivisionCode.assign(value); }

    /**
     * <p>The code for a country's subdivision (e.g., a province of Canada). A
     * subdivision code is only valid with the appropriate country code.</p>
     * <p>Constraint: Specifying <code>SubdivisionCode</code> without
     * <code>CountryCode</code> returns an <code>InvalidInput</code> error.</p>
     */
    inline GetGeoLocationRequest& WithSubdivisionCode(const Aws::String& value) { SetSubdivisionCode(value); return *this;}

    /**
     * <p>The code for a country's subdivision (e.g., a province of Canada). A
     * subdivision code is only valid with the appropriate country code.</p>
     * <p>Constraint: Specifying <code>SubdivisionCode</code> without
     * <code>CountryCode</code> returns an <code>InvalidInput</code> error.</p>
     */
    inline GetGeoLocationRequest& WithSubdivisionCode(Aws::String&& value) { SetSubdivisionCode(value); return *this;}

    /**
     * <p>The code for a country's subdivision (e.g., a province of Canada). A
     * subdivision code is only valid with the appropriate country code.</p>
     * <p>Constraint: Specifying <code>SubdivisionCode</code> without
     * <code>CountryCode</code> returns an <code>InvalidInput</code> error.</p>
     */
    inline GetGeoLocationRequest& WithSubdivisionCode(const char* value) { SetSubdivisionCode(value); return *this;}

  private:
    Aws::String m_continentCode;
    bool m_continentCodeHasBeenSet;
    Aws::String m_countryCode;
    bool m_countryCodeHasBeenSet;
    Aws::String m_subdivisionCode;
    bool m_subdivisionCodeHasBeenSet;
  };

} // namespace Model
} // namespace Route53
} // namespace Aws
