TEMPLATE = subdirs
include(../config.pri)


CONFIG += ordered
SUBDIRS = common


maemo5: {
  SUBDIRS += maps \
             json \
	     http_requests \ 
             tracker
	     
}

linux: {
  SUBDIRS += \
             json \
             http_requests \
             maps \ 
	           tracker\ 
             service \
}

symbian: {
}


