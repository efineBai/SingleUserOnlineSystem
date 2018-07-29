all: android ios localhost

GypAndroid.mk: libsingleuser.gyp  ./deps/djinni/support-lib/support_lib.gyp UserLogin.djinni
	 sh ./run_djinni.sh
	ANDROID_BUILD_TOP=$(shell dirname `which ndk-build`) deps/gyp/gyp --depth=. -f android -DOS=android -Ideps/djinni/common.gypi ./libsingleuser.gyp --root-target=libsingleuser


android: GypAndroid.mk
	cd SingleUserOnlineApp/ && ./gradlew app:assembleDebug --info
	@echo "Apks produced at:"
	@python deps/djinni/example/glob.py ./ '*.apk'

