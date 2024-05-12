#pragma once

#include <string>

/**
 * @file
 * @brief Pem strings used by @ref S31::Utils::Test::createCertificateRevocation().
 *
 * @details
 * The Pem strings in this file are duplicates of DFL/Crypto/Private/TestRootCaPemStrings.h
 * that are used to creating a certificate revocation list for testing.
 * These should be removed when %DFL::Crypto provides a revocation list creation utility
 *
 * @ingroup S31Utils
 */

namespace S31::Nomenclature::Test::Impl
{
/// @brief The root ca certificate string for creating a certificate revocation list
/// @ingroup S31Utils
const std::string rootCaCertString(
    "-----BEGIN CERTIFICATE-----\n"
    "MIIF6TCCA9GgAwIBAgIJAMPX87Sb5tiIMA0GCSqGSIb3DQEBCwUAMEcxCzAJBgNV\n"
    "BAYTAkRFMRAwDgYDVQQKEwdEcmFlZ2VyMSYwJAYDVQQDEx1EcmFlZ2VyIERldmlj\n"
    "ZSBSb290IENBIC0gVGVzdDAgFw0xNzA2MjYwOTIwMjdaGA8yMDYyMDYxNTA5MjAy\n"
    "N1owRzELMAkGA1UEBhMCREUxEDAOBgNVBAoTB0RyYWVnZXIxJjAkBgNVBAMTHURy\n"
    "YWVnZXIgRGV2aWNlIFJvb3QgQ0EgLSBUZXN0MIICIjANBgkqhkiG9w0BAQEFAAOC\n"
    "Ag8AMIICCgKCAgEA3DJolD+PSob+7J6QY1Kyxi1+kgw+ymuLNltbM1cWeilkGsXt\n"
    "Iw9nGdp17ZKUFV50L/5TpayLGagdyqkeYWnFK6vxxnw9ogc+/FfBGI4+iUL+AK7L\n"
    "K4kOr/n/OUcIXvLh5odCnLBn81scQHUvaiiMOLKys3JtZ/oCnbzmet7/SL2HgyT6\n"
    "btND7UEVbDli8zac3k+lmWPl2uh1yaaFSAwBxMqVCNIjiyMLV8z8Foq28Sg+caxa\n"
    "lwO2YhIy6jl/sTm73MMYhde/VJ6Ga2fK2lbjBcSgPwEULUs09byUkkL5evdc2cbr\n"
    "2qehRmVIlvp9K+TmNIkrbzIHPwPwC7cOdco4RcAsxF0IPpCE4OSJZ8jURsmuQwah\n"
    "Klhc6VE9PUfjnqkDdHo6K7y1T1l6dQHYWX5KFz1laIclkx+r+pXeAh6MuJNTlNCe\n"
    "RNsoGXwOD90/HA2BOkHPNH0unpWU9FZBtEmw6DT7wvZvGO315Dy8jD0X7tuq1Qye\n"
    "PVF8z+fhjJbz3nrH1+O7A4IndaHlrJwefFZum/Z9BabUiDtRaICrGVFtfNFAURv1\n"
    "ocVEW9xnionVUjQuY6kH6M7bMNaidD5KoY6G7wWimkt7cEWVZ02fxiiSwg65uELn\n"
    "9uozHU72YFoWIoKka4C632gnChsArb2ZrmLWhRQEi+kaUv5ZACJX8fDIvQUCAwEA\n"
    "AaOB1TCB0jAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4E\n"
    "FgQUmTulZ1s+sQK2AsbYhB+FEtWEvugwHwYDVR0jBBgwFoAUmTulZ1s+sQK2AsbY\n"
    "hB+FEtWEvugwbwYDVR0gBGgwZjBkBgpghXQBWQEFAQIBMFYwVAYIKwYBBQUHAgEW\n"
    "SGh0dHA6Ly93d3cuZHJhZWdlci5jb20vc2VjdXJpdHkvcGtpL3JlcG9zaXRvcnkv\n"
    "RHJhZWdlci1EZXZpY2UtQ1AtQ1BTLnBkZjANBgkqhkiG9w0BAQsFAAOCAgEANMLs\n"
    "g/gEASpt/4zQ8b0GXP49ouTMH0jbBN4V5fp2zUxE3+AqJjyj9yUgrrpdM+iMka+/\n"
    "aQr7O5xegS2TRXFHYmDuYoB7nTQWGb1iSGhqtUWTXpuznLFLd1NBi8kLKwguL8C+\n"
    "zupGthA0Oa5nPybfd41lmA4zOCDyjK4rTjyPlMH3RHexAVip2dR/ByfzKpgNeYxL\n"
    "S5aQlOy0d9rMhLouzs9TwazneaCpKA3k2H9qw9KITEeWqUSetKQbQNmquu7Jw4i0\n"
    "4mhGNHTph2bR+veocZYmFBokHx+yzcS32SQ9DZ+8tvUxlq0ex4omGhXL3xkLGi0/\n"
    "8XMhzR0ZmjLBdnwaG1x88X7gKW/cyF/ZbYdvPyiy0QRHR4GPiVDRyfwIXcb1xYen\n"
    "EvBCz4Dz5Y7dyizCU3e5CHwmsMxAkLZJZWtUrvz4cehdIBKM1M2/B+/VZ7JaJ4KM\n"
    "faeA9pARsyBhcDfayOrxYUC/IzakCMXrW/rXGG3V89u99jQcf7dIbm63xIplZNeQ\n"
    "T6BZg2qwrxgRVYXSZRPikTqlWEux3hiwW5VPRIXGdxfp8MYEm8ubrV5SKyDJB1ZB\n"
    "6Y15g5elJ/2j/3M2NJ8GNOaYCNRyn9HS5Ag+Qy0dfU6Lwk07RpbelkviMMJfHckX\n"
    "b5jPSFySk1UndfFHSz2LTukhJvHsN45mMI56rUA=\n"
    "-----END CERTIFICATE-----\n"
);

/// @brief The root private key string for signing a certificate revocation list
/// @ingroup S31Utils
const std::string rootCaCertKey(
    "-----BEGIN RSA PRIVATE KEY-----\n"
    "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\n"
    "-----END RSA PRIVATE KEY-----\n"
);

}
