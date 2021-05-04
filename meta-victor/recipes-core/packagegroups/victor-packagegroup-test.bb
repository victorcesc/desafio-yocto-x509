DESCRIPTION = "teste de pacotes"
SUMMARY = "teste"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

RDEPENDS_$ = "\
  openssl \
  apache2 \
  php"

