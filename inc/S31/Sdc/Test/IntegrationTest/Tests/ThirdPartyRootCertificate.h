#pragma once

namespace S31::Sdc::Test
{

/*
Content of the following certificate

Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            1d:dc:99:19:82:19:86:82:5d:22:41:d0:78:fd:fd:d6:15:89:8f:24
        Signature Algorithm: sha256WithRSAEncryption
        Issuer: CN = Test Third Party Root, C = CU, O = There is no party like the third party
        Validity
            Not Before: Jun  2 14:17:02 2021 GMT
            Not After : May  9 14:17:02 2121 GMT
        Subject: CN = Test Third Party Root, C = CU, O = There is no party like the third party
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                RSA Public-Key: (4096 bit)
                Modulus:
                    00:df:aa:03:59:91:2f:1e:08:0e:0f:ab:18:fb:f5:
                    38:fe:d9:8d:48:35:87:fa:0b:ee:b1:da:47:b5:a0:
                    a4:95:da:4f:5c:52:1c:be:7a:a0:48:ce:4a:8d:c5:
                    c6:b8:74:fe:d7:71:78:fd:e3:95:48:89:a5:c2:d7:
                    13:88:6f:ad:50:65:29:fe:88:f4:a3:7f:e7:46:76:
                    bb:ad:94:f2:d3:47:22:0c:fe:b8:4b:95:b8:b7:4c:
                    25:0c:b2:0e:0a:03:c7:a9:2a:e6:8b:d0:a1:e2:40:
                    53:c6:5a:4d:94:7a:7d:f9:55:ba:e2:ed:a5:83:fd:
                    1c:a1:d4:7c:3b:f3:56:88:94:52:16:54:f1:cb:65:
                    04:a4:4a:7d:2e:90:9a:f3:db:8d:25:fc:b5:5f:1d:
                    2c:2e:6c:9d:6b:5e:a0:50:d1:02:b5:c0:53:ff:d7:
                    3f:af:97:2a:4f:a7:ac:27:d2:88:28:63:f8:70:dc:
                    e8:38:44:7b:47:c5:c5:5e:0b:08:33:59:4a:d5:0d:
                    05:af:75:20:5e:7a:55:b3:6b:f5:23:37:48:31:05:
                    f7:4c:da:bd:a6:00:68:ba:b1:de:40:53:24:b1:20:
                    46:f8:7b:94:dc:33:89:40:d2:0d:a2:44:9c:b7:9d:
                    9e:5f:a3:7d:a5:07:b4:95:27:a2:cc:8c:da:5c:27:
                    27:57:7c:df:1c:b1:b2:8d:e1:a3:7d:9a:1b:c0:92:
                    81:c9:f7:04:54:9a:32:1c:61:ee:40:06:1a:53:7f:
                    d9:70:74:0c:10:56:b6:a4:6f:32:87:cd:8b:42:62:
                    bf:31:7d:a9:f8:4f:28:c5:ab:75:7c:42:aa:56:1b:
                    f5:bd:13:d8:9d:a3:1f:4c:f3:22:01:57:29:b0:15:
                    9a:59:51:8e:29:70:1f:d5:4b:ad:aa:9f:13:65:a8:
                    f7:06:ed:5a:9e:8c:2f:58:6d:bd:e9:ae:da:51:68:
                    48:b4:54:3e:c7:11:68:20:2a:67:96:56:61:09:c3:
                    eb:cf:0f:79:0a:77:25:fe:60:2d:68:69:51:a6:5b:
                    6e:49:ad:c3:12:c9:95:6d:6a:9d:03:07:46:43:8c:
                    5f:17:77:ed:10:58:f3:43:4b:1b:76:78:c2:96:5b:
                    5a:97:7b:f1:95:81:fe:1a:8b:ec:4d:51:83:1f:b5:
                    75:e5:c3:5b:f3:57:e4:cc:44:36:36:5a:c6:20:f8:
                    ff:b5:6f:53:5e:8f:02:25:e2:9c:2f:ae:e8:4c:f8:
                    f3:cd:aa:46:cb:5f:b4:47:c3:3b:26:4d:63:16:bb:
                    e5:fa:85:33:1a:9d:16:58:f5:39:05:00:58:4b:c6:
                    6b:f2:8c:31:5f:6f:e7:f1:ce:89:5c:ce:a8:37:c4:
                    3f:05:99
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Subject Key Identifier:
                A4:D3:46:E0:78:0C:99:3F:C6:57:E9:4D:AE:9D:07:69:63:D0:E5:6A
            X509v3 Authority Key Identifier:
                keyid:A4:D3:46:E0:78:0C:99:3F:C6:57:E9:4D:AE:9D:07:69:63:D0:E5:6A
                DirName:/CN=Test Third Party Root/C=CU/O=There is no party like the third party
                serial:1D:DC:99:19:82:19:86:82:5D:22:41:D0:78:FD:FD:D6:15:89:8F:24

            X509v3 Basic Constraints: critical
                CA:TRUE, pathlen:0
            X509v3 Key Usage: critical
                Digital Signature, Certificate Sign, CRL Sign
    Signature Algorithm: sha256WithRSAEncryption
         49:bc:ec:42:88:e6:b3:ec:1f:1e:a5:43:57:67:53:65:f1:9b:
         4a:59:34:4f:ef:2d:c7:07:9a:94:d3:3f:56:37:d3:72:27:bc:
         06:c1:a7:f6:c8:42:27:f0:2c:80:ee:bf:c3:da:9f:c6:32:86:
         36:93:07:1e:84:20:3e:c6:00:3b:96:05:da:81:bb:90:c8:28:
         fe:94:ac:f4:f4:5d:fa:70:27:9e:63:93:6a:f2:3f:68:53:a9:
         74:a1:f5:bb:9a:24:63:b3:bd:2f:1b:38:1a:8c:55:61:40:8c:
         7e:2f:c0:09:8a:50:cf:a0:95:d4:ce:e3:26:37:ce:58:4f:a9:
         15:46:71:fa:c6:74:48:c0:8e:01:ed:3a:0e:1c:0b:da:e0:1b:
         68:a8:1e:b0:35:5b:90:f7:7c:2b:40:0c:9a:e6:32:0e:d8:79:
         15:95:d7:44:20:3f:8f:2d:9f:5c:bd:7a:65:5e:39:30:d3:c9:
         85:44:4a:10:a4:99:15:25:23:ae:5a:5d:ba:84:ec:95:dc:c3:
         3e:03:43:4c:7d:e4:e9:f3:6a:8b:45:fa:1f:3c:82:27:11:de:
         d1:9c:69:23:18:66:fa:0e:d0:ba:42:4e:51:61:98:04:b8:6e:
         26:da:dc:06:64:a9:80:2c:0b:f9:02:5d:20:f7:dd:03:55:ea:
         3f:99:25:2a:25:05:b8:19:f7:87:fb:87:54:ac:e6:c1:74:35:
         8a:c6:0f:fa:c8:92:de:52:75:ed:50:b1:88:bf:b4:9c:fd:de:
         55:08:0e:c5:0f:3c:d3:46:3f:d7:74:8e:78:82:bf:a8:a2:76:
         20:f4:ad:b4:c7:3d:3b:da:c4:ab:c8:ce:c2:b7:5d:61:f5:f3:
         05:2e:64:5f:56:42:6e:69:bb:24:ae:24:56:97:06:19:84:2c:
         07:20:89:71:71:2c:17:7a:c2:b9:2c:22:89:62:9d:cc:29:cf:
         d3:6e:f5:b4:53:e1:88:c1:ca:d2:1b:31:fe:20:b8:a2:b9:44:
         24:0d:b5:cb:0c:4b:7b:b9:18:11:ef:5e:db:61:5a:e5:15:67:
         3c:4b:d4:6d:d6:f1:4e:09:01:24:07:4a:d1:e4:88:f8:9e:0d:
         e0:d5:8e:00:d5:82:ea:92:e1:0a:59:6d:43:8c:6c:aa:a4:be:
         ad:74:f8:1e:9d:c4:dc:88:7b:ae:5a:8e:82:7e:ef:ec:59:37:
         dc:36:57:31:d5:dc:75:83:cd:61:e8:75:f8:5d:47:13:bd:a1:
         09:84:84:58:a9:1d:a5:73:5e:ca:c7:33:aa:ad:a4:47:bf:60:
         52:b0:28:41:2a:32:9d:21:6e:e2:e2:38:62:c0:b4:75:a6:54:
         82:0e:f0:32:68:e8:6e:b3

  */

const char* testThirdPartyRootCertificatePemString = R"(
-----BEGIN CERTIFICATE-----
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
MmjobrM=
-----END CERTIFICATE-----
)";

const char* testThirdPartyRootPrivateKeyPemString = R"(
-----BEGIN RSA PRIVATE KEY-----
MIIJKAIBAAKCAgEA36oDWZEvHggOD6sY+/U4/tmNSDWH+gvusdpHtaCkldpPXFIc
vnqgSM5KjcXGuHT+13F4/eOVSImlwtcTiG+tUGUp/oj0o3/nRna7rZTy00ciDP64
S5W4t0wlDLIOCgPHqSrmi9Ch4kBTxlpNlHp9+VW64u2lg/0codR8O/NWiJRSFlTx
y2UEpEp9LpCa89uNJfy1Xx0sLmyda16gUNECtcBT/9c/r5cqT6esJ9KIKGP4cNzo
OER7R8XFXgsIM1lK1Q0Fr3UgXnpVs2v1IzdIMQX3TNq9pgBourHeQFMksSBG+HuU
3DOJQNINokSct52eX6N9pQe0lSeizIzaXCcnV3zfHLGyjeGjfZobwJKByfcEVJoy
HGHuQAYaU3/ZcHQMEFa2pG8yh82LQmK/MX2p+E8oxat1fEKqVhv1vRPYnaMfTPMi
AVcpsBWaWVGOKXAf1Uutqp8TZaj3Bu1anowvWG296a7aUWhItFQ+xxFoICpnllZh
CcPrzw95Cncl/mAtaGlRpltuSa3DEsmVbWqdAwdGQ4xfF3ftEFjzQ0sbdnjCllta
l3vxlYH+GovsTVGDH7V15cNb81fkzEQ2NlrGIPj/tW9TXo8CJeKcL67oTPjzzapG
y1+0R8M7Jk1jFrvl+oUzGp0WWPU5BQBYS8Zr8owxX2/n8c6JXM6oN8Q/BZkCAwEA
AQKCAgEA0lVwpwdIdwZ+Kq/tY+x9d/Sgz3o/8J7ODwVGEIEMpjvSC/DQRTTOjQkq
xV5rfcXQbkywypn+JmQDtVJLdTAInaU1M8AZx7Qdi39XCWscXCH13KCiMbqQJhf+
c4zydOqPFgBZJLzDsCBsaAk+EdaLpzG++W8hCxm5llpbpok1JGXPOF8TsAHEtrey
N1sXzSH3//RBoDuv88yC0ZkATF/yG3fNxrfmlTskOBpnZF+xWcKBvamQ3HFSOfG7
pK/dO2TKYcbIRPNxyEdlVsC8nCx9wFRq9yRx2q1hz8g7SOSnicbf1wdouxfgCExB
NAswEeCxMiFupAa2BNpsV85R/v13GSVmal+fJLBUVGd8a0rIaWY6xhFiAB3FVy2e
LTFl18iY5N4KTk0yniAeuZQ5U00vYZNa9pN6rY4bqX0TshTy8HeWSRpgRtV3pT6c
MHSHLkrMkFQZ90oegff/rzZ1iGy59xPOhAI7Dbxda3E000PLUeaBw3MTnPYqWsdK
Rq7IHy04lvuM6IO9VkkkjYuoBqJGiKowThvWqY/sSCpSl5n4LIwKXUSDEfovHXNK
px14diiOU3JJvDEtPTjGvF8ikEQBIUjal1dpaVTt8UWnnRZILKMwpS/5FJfXKHB/
3H+FtHriHRmfiz8392WWdBuCHLugl5elczxho5lmOJmvKlwJKN0CggEBAP3aK1EX
d50hOZL0bSM9HE7hm39HDOy2C05RGE8nzaO+m1Q2DwO+MGeRyq389t+32CBGF2nv
rqjZug87R5iHX4PosUfQFlK+Rhzc0LcSVodQhqv8zfMJQfxm4he7PWrkwWY4U8LJ
jEvLLHAMkLLr9VtDOFRF+O4xPKDwHD7Y1kW8cVnuTheCx8Nk+tk3R5x5j96ZLhQU
bc6cBAoUBiPr2tDFbIxLOrFHrwvCsDR6VDBMOeXRItbVgmvIIPNkn0jcuWzvlxqb
g3ngnDwYlDoaYa7ipg/HPh/10Ja9MJ8DTNYkApKfL2DzKNwyJk3D+0KItiS+Awbz
GJJIWo9JRprj7usCggEBAOGOdT8WRxjgs9KlkVZScoExh6uxXvhRhOTS4IP5/D3/
CVLwYnrsYi/NRd2LeNV8qacY1m3hKjBbxTKo4Bsbp0JyTH700a9A0HKlp0WUDJ8r
IjWHK01fS4s5+j/krU3+EPBYdtQD1/e0PZ+zGwW4lbgcY1aRYZFytUiC3b3jDaeo
S+ABs8USv3WtQ+4zh2m8xgCkcVzfqQ6BwB8gKZDXfxgXPlMhoO7UfG1iWMqdK2o+
ZSzUAiT5DuGWKFcO08ZUEUlDR4pRun/D2VRVIcjyJPIxc+WnuGk2Q0UY/YFWnO4/
6RHmCgT1Rh1QauQduU2SYdllbxYBqbl9iHsLb05Z5IsCggEALGKwPj6PMI81pOdO
CeJOh9BUwv1mWiE+etQdHwIDp8TVHfVRzMK9be6E9MUNWXKovIPk5iX9cRKYwL8J
tra80bCnBrpwnMkeMz+80rXHIWPIGFxcmkkdG4fVsnaPt5gF5NymcKGTAVGmFHVt
+4rcXLe1Kq8NZoB/bFhvZ+G8HXdkjmfniZ7ZVOXcIozS3Z43tKEt+F7WEFEhN63m
oPNFUEmkwCcLPSIejjzdWF+nRsadPPzDTbMJWdUlRclrPG8zkMOXtRRJ+c53It7d
VAd22wBQLuQUjbwKW8D6tmL6VVr4hDCHNTlvBIlUPzasQSbsSiJbHyT0P+ecxf72
9HA0PwKCAQA6AmBnHDymykuVNl29nLC0R1/EKXbqWFTcYNu7NZTJAQmN2iMJyDes
YZfBVbh693fOcNXdJpaqH0AFOmeAsUkADtNbp20yLHIvuijd/SiN2xMOPzhEyuhr
4zpYKmDj+R60IZxWBLMLksByjSa6/vEKi8qEnhlAxgaXooiS6I0/fEofT3DDk4HI
KwqYfYorCJDH44MARsl84KPfnW7zQGkAciHmUXTJV760hyGc4nUi+u8ca14t0hwg
qnSvhzGyBTb456PDkCdt6pm/VbG9s4ELBOrwuoT0Ei+U2st/8x2jLK6tmsMi6U3i
BieniXl52NbviWXbfAwBl6Z9NsCmnvnnAoIBADS9BomsiHqA604oGCVb0rY46eao
LBONyHP6zSzFtmswMUHdX8Ef9XXy6XXpWusu7UGqc4T96pl4EYHxBRjABKtoAJJ+
UrLP+dnthzas70z8cwyl5Mm4AeicZgrIKZg5f1PCbq1w5cMqXSVUW+ihGBNAIGsj
GEJ/g0hLd4zS89Rx+Y5u0jcf4XF9P7nBUpdvHL+4qXW66j3IDHD8MoDRCUJLEvFk
nwfYEw8OrpevkASqAH9YpMDbaeX3qvNunSFNqJGC16zex1+jKlMRJowTKCY7QB0f
erj5pSH8y3nuT1wwochpwYZm3sthOF0JPxBUZqUxKNHxS12UyCsmYd0qzM8=
-----END RSA PRIVATE KEY-----
)";

}
