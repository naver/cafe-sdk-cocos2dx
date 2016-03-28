package org.cocos2dx.plugin;

import com.naver.glink.android.sdk.Glink;
import com.naver.glink.android.sdk.Glink.OnClickAppSchemeBannerListener;
import com.naver.glink.android.sdk.Glink.OnSdkStartedListener;
import com.naver.glink.android.sdk.Glink.OnSdkStoppedListener;

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
		
		Glink.setOnSdkStoppedListener(new OnSdkStoppedListener() {
			@Override
			public void onSdkStopped() {
				PluginWrapper.runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnSdkStopped();
					}
				});
			}
		});
		
		Glink.setOnClickAppSchemeBannerListener(new OnClickAppSchemeBannerListener() {
			@Override
			public void onClickAppSchemeBanner(final String appScheme) {
				PluginWrapper.runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnClickAppSchemeBanner(appScheme);
					}
				});
			}			
		});
	}
	
	private static native void nativeOnSdkStarted();
	private static native void nativeOnSdkStopped();
	private static native void nativeOnClickAppSchemeBanner(String appScheme);
	
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
