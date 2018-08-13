VERSION=	10.3.8
MARIADB_VER=	mariadb-10.3

post-install:
	${POST_INSTALL}
	cp ${FILESDIR}/my.cnf ${PREFIX}/${MARIADB_VER}/share/examples/ && \
		chown _mysql:_mysql ${PREFIX}/${MARIADB_VER}/share/examples/my.cnf

.include <bsd.port.mk>
