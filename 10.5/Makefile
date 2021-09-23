VERSION=	10.5.12
MARIADB_VER=	mariadb-10.5
PKGSTEM=	mariadb-current-10.5

post-install:
	${POST_INSTALL}
	cp ${FILESDIR}/my.cnf ${PREFIX}/${MARIADB_VER}/share/examples/ && \
		chown _mysql:_mysql ${PREFIX}/${MARIADB_VER}/share/examples/my.cnf

.include <bsd.port.mk>
