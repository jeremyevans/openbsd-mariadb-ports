# archs with atomic ops
ONLY_FOR_ARCHS?=	alpha aarch64 amd64 i386 mips64 mips64el powerpc sparc64

COMMENT?=	multithreaded SQL database

DISTNAME?=	mariadb-${VERSION}
PKGNAME?=	mariadb-current-${VERSION}

CATEGORIES?=	databases
MASTER_SITES?=	http://mariadb.mirror.iweb.com//${DISTNAME}/source/ \
		http://ftp.osuosl.org/pub/mariadb/${DISTNAME}/source/ \

LIB_VERSION?=	28
SHARED_LIBS?=	mysqlclient_r	${LIB_VERSION}.0 \
		mysqlclient	${LIB_VERSION}.0 \
		mariadb		${LIB_VERSION}.0

HOMEPAGE?=	http://mariadb.org/

# GPLv2 and LGPLv2.1
PERMIT_PACKAGE ?=	Yes

WANTLIB?=	c curses crypto iconv m pthread readline ssl ${COMPILER_LIBCXX} z

LOCALSTATEDIR?=	${BASELOCALSTATEDIR}/${MARIADB_VER}
SOCKET_DIR?=	/var/run/${MARIADB_VER}
SUBST_VARS?=	SOCKET_DIR MARIADB_VER

MODULES?=	devel/cmake
BUILD_DEPENDS?=	devel/bison

LIB_DEPENDS?=	converters/libiconv
RUN_DEPENDS?=	databases/p5-DBD-mysql

CONFIGURE_ARGS+=-DCMAKE_INSTALL_PREFIX="${PREFIX}/${MARIADB_VER}" \
		-DINSTALL_SYSCONFDIR="/etc/${MARIADB_VER}" \
		-DINSTALL_DOCDIR="share/doc" \
		-DINSTALL_DOCREADMEDIR="share/doc" \
		-DINSTALL_INCLUDEDIR="include" \
		-DINSTALL_INFODIR="info" \
		-DINSTALL_LIBDIR="lib" \
		-DINSTALL_MANDIR="man" \
		-DINSTALL_MYSQLDATADIR="${LOCALSTATEDIR}" \
		-DINSTALL_MYSQLSHAREDIR="share/mariadb" \
		-DINSTALL_MYSQLTESTDIR="share/mariadb-test" \
		-DINSTALL_PLUGINDIR="lib/plugin" \
		-DINSTALL_SBINDIR="libexec" \
		-DINSTALL_SCRIPTDIR="bin" \
		-DINSTALL_SHAREDIR="share" \
		-DINSTALL_SQLBENCHDIR="share/mariadb-bench" \
		-DINSTALL_SUPPORTFILESDIR="share/examples/" \
		-DMYSQL_UNIX_ADDR="${SOCKET_DIR}/mariadb.sock" \
		-DCOMPILATION_COMMENT='OpenBSD port: ${FULLPKGNAME}' \
		-DWITH_PCRE=bundled \
		-DWITH_SSL=system \
		-DCONNECT_WITH_LIBXML2=Off

# The Mroonga and TokuDB storage engines do not build at the
# moment on OpenBSD.
# It is still not enabled due to a linking issue with liblz4.
CONFIGURE_ARGS+=-DWITHOUT_MROONGA_STORAGE_ENGINE=1
# One more or more issues to look into.
CONFIGURE_ARGS+=-DWITHOUT_TOKUDB_STORAGE_ENGINE=1
# RocksDB requires timer_delete
CONFIGURE_ARGS+=-DWITHOUT_ROCKSDB_STORAGE_ENGINE=1

pre-configure:
	${SUBST_CMD} ${WRKSRC}/cmake/mysql_version.cmake

POST_INSTALL ?= cd ${PREFIX}/${MARIADB_VER}/lib && \
		ln -sf libmariadb.so.${LIBmariadb_VERSION} libmysqlclient.so.${LIBmysqlclient_VERSION} && \
		ln -sf libmariadb.so.${LIBmariadb_VERSION} libmysqlclient_r.so.${LIBmysqlclient_r_VERSION}; \
		rm -rf ${PREFIX}/${MARIADB_VER}/share/mariadb-test/

do-regress:
	cd ${WRKBUILD}/mysql-test && ./mysql-test-run.pl --force --verbose --max-test-fail=0
