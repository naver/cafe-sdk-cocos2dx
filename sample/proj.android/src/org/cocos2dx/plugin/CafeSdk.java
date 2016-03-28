package org.cocos2dx.plugin;

import com.naver.glink.android.sdk.Glink;
import com.naver.glink.android.sdk.Glink.OnSdkStartedListener;

import android.app.Activity;
import android.content.Context;

public class CafeSdk {
	private static Activity mContext;

	public CafeSdk(Context context) {
		mContext = (Activity) context;
	}

	public void init(String clientId, String clientSecret, int cafeId) {
		Glink.init(clientId, clientSecret, cafeId);
		
		Glink.setOnSdkStartedListener(new OnSdkStartedListener() {
			@Override
			public void onSdkStarted() {
				PluginWrapper.runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnSdkStarted();
					}
				});
			}
		});
	}

	private static native void nativeOnSdkStarted();
	
	public void startHome() {
		Glink.startHome(mContext);
	}

	public void startProfile() {
		Glink.startProfile(mContext);
	}
	
	public void startImageWrite(int menuId, String subject, String text, String imageUri) {
		Glink.startImageWrite(mContext, menuId, subject, text, imageUri);
	}
}
