package org.cocos2dx.plugin;

import com.naver.glink.android.sdk.Glink;
import com.naver.glink.android.sdk.Glink.OnClickAppSchemeBannerListener;
import com.naver.glink.android.sdk.Glink.OnJoinedListener;
import com.naver.glink.android.sdk.Glink.OnPostedArticleListener;
import com.naver.glink.android.sdk.Glink.OnPostedCommentListener;
import com.naver.glink.android.sdk.Glink.OnSdkStartedListener;
import com.naver.glink.android.sdk.Glink.OnSdkStoppedListener;

import android.app.Activity;
import android.content.Context;
import android.widget.Toast;

public class CafeSdk {

	public CafeSdk(Context context) {
		// do nothing.
	}

	private Activity getActivity() {
		return (Activity) PluginWrapper.getContext();
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
		
		Glink.setOnJoinedListener(new OnJoinedListener() {
			@Override
			public void onJoined() {
				PluginWrapper.runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnJoined();
					}
				});
			}
		});
		
		Glink.setOnPostedArticleListener(new OnPostedArticleListener() {
			@Override
			public void onPostedArticle(final int menuId) {
				PluginWrapper.runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnPostedArticle(menuId);
					}
				});
			}
		});
		
		Glink.setOnPostedCommentListener(new OnPostedCommentListener() {
			@Override
			public void onPostedComment(final int articleId) {
				PluginWrapper.runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnPostedComment(articleId);
					}
				});
			}
		});
	}
	
	private static native void nativeOnSdkStarted();
	private static native void nativeOnSdkStopped();
	private static native void nativeOnClickAppSchemeBanner(String appScheme);
	private static native void nativeOnJoined();
	private static native void nativeOnPostedArticle(int menuId);
	private static native void nativeOnPostedComment(int articleId);
	
	public void startHome() {
		Glink.startHome(getActivity());
	}

	public void startNotice() {
		Glink.startNotice(getActivity());
	}
	
	public void startEvent() {
		Glink.startEvent(getActivity());
	}
	
	public void startMenu(int menuId) {
		if (menuId == -1) {
			Glink.startMenu(getActivity());			
		} else {
			Glink.startMenu(getActivity(), menuId);
		}
	}
	
	public void startProfile() {
		Glink.startProfile(getActivity());
	}
	
	public void startWrite(int menuId, String subject, String text) {
		Glink.startWrite(getActivity(), menuId, subject, text);
	}
	
	public void startImageWrite(int menuId, String subject, String text, String imageUri) {
		Glink.startImageWrite(getActivity(), menuId, subject, text, imageUri);
	}
	
	public void startVideoWrite(int menuId, String subject, String text, String videoUri) {
		Glink.startVideoWrite(getActivity(), menuId, subject, text, videoUri);
	}
	
	public void syncGameUserId(String gameUserId) {
		Glink.syncGameUserId(getActivity(), gameUserId);
	}
	
	public boolean isShowGlink() {
		return Glink.isShowGlink(getActivity());
	}
	
	public void showToast(final String text) {
		getActivity().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(getActivity(), text, Toast.LENGTH_LONG).show();
			}
		});
	}
}
