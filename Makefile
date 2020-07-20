
HOST_OS        ?= $(shell uname|tr '[A-Z]' '[a-z]')
NODE           ?= node
ANDROID_JAR     = out/android.classs.ftr.jar
FTRP            = ./libs/ftrp
FTRP_OUT        = out/ftrp
GIT_repository := $(shell git remote -v|grep origin|tail -1|awk '{print $$2}'|cut -d "/" -f 1)
REMOTE_COMPILE_HOST ?= 192.168.0.115

ifneq ($(USER),root)
	SUDO := "sudo"
endif

ifeq ($(HOST_OS),darwin)
	HOST_OS := osx
endif

ifeq ($(GIT_repository),)
	GIT_repository = https://github.com/louis-tru
endif

#######################

DEPS = libs/somes libs/ftrp/gyp.ftr depe/v8-link \
		depe/FFmpeg.ftr depe/node.ftr depe/bplus depe/skia
FORWARD = make xcode msvs make-linux cmake-linux cmake build $(ANDROID_JAR) test2 clean

git_pull=sh -c "\
	if [ ! -f $(1)/.git/config ]; then \
		git clone $(3) $(1) && cd $(1) && git checkout $(2) && echo git clone $(3) ok; \
	else \
		cd $(1) && git pull && git checkout $(2) && echo git pull $(1) ok; \
	fi"

git_push=sh -c "cd $(1) && git push && echo git push $(1) ok"

git_pull_deps=echo $(1) deps \
	$(foreach i,$(DEPS),&& \
		$(call git_$(1),\
			$(call basename,$(i)),\
			$(if $(call suffix,$(i)),$(call subst,.,,$(call suffix,$(i))),master),\
			$(GIT_repository)/$(call subst,$(call suffix,$(i)),,$(call notdir,$(i))).git\
		) \
	)

check_osx=\
	if [ "$(HOST_OS)" != "osx" ]; then \
		echo ;\
		echo target \"$(1)\" can only run on MAC system.;\
		echo ;\
		exit 1; \
	fi

.PHONY: $(FORWARD) ios android linux osx \
	product install install-ftrp \
	help web doc watch all all_on_linux all_on_osx pull push

.SECONDEXPANSION:

# compile product ftr and install
# It can only run in MAC system.
product:
	@$(MAKE) ios
	@$(MAKE) android
	@$(NODE) ./tools/cp-ftrp.js

install: product
	@$(MAKE) install-ftrp

install-ftrp:
	@$(NODE) ./tools/cp-ftrp.js
	@cd $(FTRP_OUT) && npm i -f
	@cd $(FTRP_OUT) && $(SUDO) npm i -g

$(FORWARD):
	@$(MAKE) -f build.mk $@

# build all ios platform and output to product dir
# It can only run in MAC system.
ios:
	@$(call check_osx,$@)
	@#./configure --os=ios --arch=arm --library=shared && $(MAKE) build # armv7 say goodbye 
	@./configure --os=ios --arch=x64   --library=shared && $(MAKE) build
	@./configure --os=ios --arch=arm64 --library=shared && $(MAKE) build
	@./configure --os=ios --arch=arm64 --library=shared -v8 --suffix=arm64.v8 && $(MAKE) build # handy debug
	@./tools/gen_apple_frameworks.sh $(FTRP_OUT) ios

# build all android platform and output to product dir
android:
	@./configure --os=android --arch=x64   --library=shared && $(MAKE) build
	@./configure --os=android --arch=arm   --library=shared && $(MAKE) build
	@./configure --os=android --arch=arm64 --library=shared && $(MAKE) build
	@$(MAKE) $(ANDROID_JAR)

linux:
	@./configure --os=linux   --arch=x64   --library=shared && $(MAKE) build
	@./configure --os=linux   --arch=arm   --library=shared && $(MAKE) build
	@./configure --os=linux   --arch=x64                    && $(MAKE) build
	@./configure --os=linux   --arch=arm                    && $(MAKE) build

osx:
	@$(call check_osx,$@)
	@echo Unsupported

# build all from current system platform

all:
	@if [ "$(HOST_OS)" = "osx" ]; then \
		$(MAKE) all_on_osx; \
	elif [ "$(HOST_OS)" = "linux" ]; then \
		$(MAKE) all_on_linux; \
	else \
		echo Unsupported current System "$(HOST_OS)"; \
	fi

all_on_osx:
	@$(MAKE) android
	@$(MAKE) ios
	@./configure --os=ios     --arch=arm   --library=shared && $(MAKE) build
	@./configure --os=android --arch=x86   --library=shared && $(MAKE) build
	@./configure --os=android --arch=x86                    && $(MAKE) build
	@./configure --os=android --arch=x64                    && $(MAKE) build
	@./configure --os=android --arch=arm                    && $(MAKE) build
	@./configure --os=android --arch=arm64                  && $(MAKE) build

all_on_linux:
	@$(MAKE) android
	@$(MAKE) linux
	@./configure --os=android --arch=x86   --library=shared && $(MAKE) build
	@./configure --os=android --arch=x86                    && $(MAKE) build
	@./configure --os=android --arch=x64                    && $(MAKE) build
	@./configure --os=android --arch=arm                    && $(MAKE) build
	@./configure --os=android --arch=arm64                  && $(MAKE) build

doc:
	@$(NODE) tools/gen_html_doc.js docs out/docs

web:
	@$(NODE) --inspect=0.0.0.0:9228 tools/server.js

help:
	@echo
	@echo Run \"make\" start build product
	@echo Run \"make xcode\" output xcode project file
	@echo You must first call before calling make \"./configure\"
	@echo

watch:
	@./tools/sync_watch -h $(REMOTE_COMPILE_HOST)

pull:
	@git pull
	@if [ ! -f test/android/app/app.iml ]; then \
		cp test/android/app/.app.iml test/android/app/app.iml; \
	fi
	@$(call git_pull_deps,pull)

push:
	@git push
	@$(call git_pull_deps,push)