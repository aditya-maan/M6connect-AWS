<?php
/**
 * This file is automatically @generated by {@link BuildMetadataPHPFromXml}.
 * Please don't modify it directly.
 */


return array (
  'generalDesc' => 
  array (
    'NationalNumberPattern' => '[1-467-9]\\d{2,5}',
    'PossibleNumberPattern' => '\\d{3,6}',
  ),
  'fixedLine' => 
  array (
    'NationalNumberPattern' => '[1-467-9]\\d{2,5}',
    'PossibleNumberPattern' => '\\d{3,6}',
  ),
  'mobile' => 
  array (
    'NationalNumberPattern' => '[1-467-9]\\d{2,5}',
    'PossibleNumberPattern' => '\\d{3,6}',
  ),
  'tollFree' => 
  array (
    'NationalNumberPattern' => '
          1(?:
            16\\d{3}|
            7[56]0|
            8000
          )|
          2(?:
            202|
            48
          )|
          4444
        ',
    'PossibleNumberPattern' => '\\d{3,6}',
    'ExampleNumber' => '116000',
  ),
  'premiumRate' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'sharedCost' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'personalNumber' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'voip' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'pager' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'uan' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'emergency' => 
  array (
    'NationalNumberPattern' => '
          112|
          999
        ',
    'PossibleNumberPattern' => '\\d{3}',
    'ExampleNumber' => '112',
  ),
  'voicemail' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'shortCode' => 
  array (
    'NationalNumberPattern' => '
          1(?:
            0[01]|
            1(?:
              [12]|
              6(?:
                000|
                1(?:
                  11|
                  23
                )
              )|
              8\\d{3}
            )|
            2[123]|
            33|
            4(?:
              1|
              7\\d
            )|
            5(?:
              \\d|
              71
            )|
            7(?:
              0\\d|
              [56]0
            )|
            800\\d|
            9[15]
          )|
          2(?:
            02(?:02)?|
            1300|
            2(?:
              02|
              11|
              2
            )|
            3(?:
              02|
              336|
              45
            )|
            4(?:
              25|
              8
            )
          )|
          3[13]3|
          4(?:
            0[02]|
            35[01]|
            44[45]|
            5\\d
          )|
          6(?:
            50|
            \\d{4}
          )|
          7(?:
            0\\d{3}|
            8(?:
              9|
              \\d{3}
            )|
            9\\d{3}
          )|
          8\\d{4}|
          9(?:
            01|
            99
          )
        ',
    'PossibleNumberPattern' => '\\d{3,6}',
    'ExampleNumber' => '150',
  ),
  'standardRate' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'carrierSpecific' => 
  array (
    'NationalNumberPattern' => '
          1(?:
            571|
            7[56]0
          )|
          2(?:
            02(?:02)?|
            1300|
            3336|
            48
          )|
          4444|
          901
        ',
    'PossibleNumberPattern' => '\\d{3,5}',
    'ExampleNumber' => '1571',
  ),
  'noInternationalDialling' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'id' => 'GB',
  'countryCode' => 0,
  'internationalPrefix' => '',
  'sameMobileAndFixedLinePattern' => true,
  'numberFormat' => 
  array (
  ),
  'intlNumberFormat' => 
  array (
  ),
  'mainCountryForCode' => false,
  'leadingZeroPossible' => false,
  'mobileNumberPortableRegion' => false,
);