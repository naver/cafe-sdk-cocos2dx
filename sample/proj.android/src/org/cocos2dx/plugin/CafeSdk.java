package org.cocos2dx.plugin;

import com.naver.glink.android.sdk.Glink;
import com.naver.glink.android.sdk.Glink.OnSdkStartedListener;

import android.app.Activity;
import android.content.Context;
import android.widget.Toast;

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

	public void startNotice() {
		Glink.startNotice(mContext);
	}
	
	public void startEvent() {
		Glink.startEvent(mContext);
	}
	
	public void startMenu() {
		Glink.startMenu(mContext);
	}
	
	public void startProfile() {
		Glink.startProfile(mContext);
	}
	
	public void startImageWrite(int menuId, String subject, String text, String imageUri) {
		Glink.startImageWrite(mContext, menuId, subject, text, imageUri);
	}
	
	public void showToast(final String text) {
		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(mContext, text, Toast.LENGTH_LONG).show();
			}
		});
	}
}
