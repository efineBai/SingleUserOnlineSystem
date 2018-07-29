#
# Environment variables for overriding default behavior.
#

ifndef ANDROID_NDK_HOME
ANDROID_NDK_HOME = $(abspath $(dir $(realpath $(shell which ndk-build))))
endif

SCALA_VERSION=2.11
DJINNI_VERSION=0.1-SNAPSHOT
OUTPUT_JAR=src/target/scala-$(SCALA_VERSION)/djinni-assembly-$(DJINNI_VERSION).jar

#
# Global targets.
#

all: djinni SingleUserOnlineClient_ios SingleUserOnlineClient_android SingleUserOnlineClient_localhost test

clean: djinni_jar_clean
	-ndk-build -C SingleUserOnlineClient/SingleUserOnlineApp/app/ clean
	-xcodebuild -workspace SingleUserOnlineClient/objc/TextSort.xcworkspace -scheme TextSort -configuration 'Debug' -sdk iphonesimulator clean
	-rm -rf libs/
	-rm -rf obj/
	-rm -rf build/
	-rm -rf build_ios/
	-rm -f GypAndroid.mk

# rule to lazily clone gyp
# freeze gyp at the last version with android support
./deps/gyp:
	git clone https://chromium.googlesource.com/external/gyp.git ./deps/gyp
	cd deps/gyp && git checkout -q 0bb67471bca068996e15b56738fa4824dfa19de0

djinni:
	cd src && ./build

$(OUTPUT_JAR):
	cd src && sbt assembly

djinni_jar: $(OUTPUT_JAR)

djinni_jar_clean:
	cd src && sbt clean

# we specify a root target for android to prevent all of the targets from spidering out
GypAndroid.mk: ./deps/gyp SingleUserOnlineClient/libtextsort.gyp support-lib/support_lib.gyp SingleUserOnlineClient/UserLogin.djinni
	./SingleUserOnlineClient/run_djinni.sh
	ANDROID_BUILD_TOP=$(ANDROID_NDK_HOME) deps/gyp/gyp --depth=. -f android -DOS=android -Icommon.gypi SingleUserOnlineClient/libtextsort.gyp --root-target=libtextsort_jni

# we specify a root target for android to prevent all of the targets from spidering out
./build_ios/SingleUserOnlineClient/libtextsort.xcodeproj: ./deps/gyp SingleUserOnlineClient/libtextsort.gyp support-lib/support_lib.gyp SingleUserOnlineClient/UserLogin.djinni
	./SingleUserOnlineClient/run_djinni.sh
	deps/gyp/gyp --depth=. -f xcode -DOS=ios --generator-output ./build_ios -Icommon.gypi SingleUserOnlineClient/libtextsort.gyp

SingleUserOnlineClient_ios: ./build_ios/SingleUserOnlineClient/libtextsort.xcodeproj
	xcodebuild -workspace SingleUserOnlineClient/objc/TextSort.xcworkspace \
           -scheme TextSort \
           -configuration 'Debug' \
           -sdk iphonesimulator

# this target implicitly depends on GypAndroid.mk since gradle will try to make it
SingleUserOnlineClient_android: GypAndroid.mk
	cd SingleUserOnlineClient/SingleUserOnlineApp/ && ./gradlew app:assembleDebug
	@echo "Apks produced at:"
	@python SingleUserOnlineClient/glob.py SingleUserOnlineClient/ '*.apk'

SingleUserOnlineClient_localhost: ./deps/java
	cd SingleUserOnlineClient && make localhost

test: ./deps/java
	make -C test-suite

.PHONY: SingleUserOnlineClient_android SingleUserOnlineClient_ios SingleUserOnlineClient_localhost test djinni clean all dinni_jar
