VERSION=	10.4.21
MARIADB_VER=	mariadb-10.4
PKGSTEM=	mariadb-current-10.4
REVISION=	0

post-install:
	${POST_INSTALL}
	cp ${FILESDIR}/my.cnf ${PREFIX}/${MARIADB_VER}/share/examples/ && \
		chown _mysql:_mysql ${PREFIX}/${MARIADB_VER}/share/examples/my.cnf

.include <bsd.port.mk>
