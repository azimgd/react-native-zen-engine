ARCHS_IOS = x86_64-apple-ios aarch64-apple-ios aarch64-apple-ios-sim
ARCHS_ANDROID = i686-linux-android aarch64-linux-android x86_64-linux-android armv7-linux-androideabi

LIB = libzen_ffi.a
DYLIB = libzenffi.so
XCFRAMEWORK = rnzensdk.xcframework

all: ios android

ios: $(XCFRAMEWORK)

android: $(ARCHS_ANDROID)
	# After build is done copy files into the android folder
	mkdir -p ../android/jniLibs
	mkdir -p ../android/jniLibs/x86
	mkdir -p ../android/jniLibs/arm64-v8a
	mkdir -p ../android/jniLibs/armeabi-v7a
	mkdir -p ../android/jniLibs/x86_64

	cp ./target/i686-linux-android/release/libzen_ffi.so ../android/jniLibs/x86/$(DYLIB)
	cp ./target/aarch64-linux-android/release/libzen_ffi.so ../android/jniLibs/arm64-v8a/$(DYLIB)
	cp ./target/x86_64-linux-android/release/libzen_ffi.so ../android/jniLibs/x86_64/$(DYLIB)
	cp ./target/armv7-linux-androideabi/release/libzen_ffi.so ../android/jniLibs/armeabi-v7a/$(DYLIB)

.PHONY: $(ARCHS_IOS)
$(ARCHS_IOS): %:
	rm -rf target simulator_fat rnzensdk.xcframework
	cargo build --target $@ --release

.PHONY: $(ARCHS_ANDROID)
$(ARCHS_ANDROID): %:
	rm -rf target simulator_fat rnzensdk.xcframework
	cargo ndk --target $@ --platform 23 build --release

$(XCFRAMEWORK): $(ARCHS_IOS)
	mkdir -p simulator_fat
	lipo -create target/x86_64-apple-ios/release/$(LIB) target/aarch64-apple-ios-sim/release/$(LIB) -output simulator_fat/$(LIB)
	xcodebuild -create-xcframework -library target/aarch64-apple-ios/release/$(LIB) -headers generated/include -library simulator_fat/$(LIB) -headers generated/include -output $@
	cp -r -f $@ ../ios/$@
