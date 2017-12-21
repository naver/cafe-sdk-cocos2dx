package com.naver.cafe;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.naver.glink.android.sdk.Glink;
import com.naver.glink.android.sdk.Glink.OnClickAppSchemeBannerListener;
import com.naver.glink.android.sdk.Glink.OnJoinedListener;
import com.naver.glink.android.sdk.Glink.OnLoggedInListener;
import com.naver.glink.android.sdk.Glink.OnPostedArticleListener;
import com.naver.glink.android.sdk.Glink.OnPostedCommentListener;
import com.naver.glink.android.sdk.Glink.OnSdkStartedListener;
import com.naver.glink.android.sdk.Glink.OnSdkStoppedListener;
import com.naver.glink.android.sdk.Glink.OnWidgetScreenshotClickListener;
import com.naver.glink.android.sdk.NaverIdLogin;
import com.naver.glink.android.sdk.PlugRecordManager;
import com.naver.glink.android.sdk.PlugRecordManager.OnRecordManagerListener;
import com.naver.glink.android.sdk.NaverIdLogin.OnGetProfileListener;
import com.naver.glink.android.sdk.Statistics;

import android.widget.Toast;

public class CafeSdk {

	private static boolean initializedListeners;

	public static Cocos2dxActivity getActivity() {
		return (Cocos2dxActivity) Cocos2dxActivity.getContext();
	}

	public static void runOnGLThread(Runnable r) {
		getActivity().runOnGLThread(r);
	}

	public static void init(String clientId, String clientSecret, int cafeId) {
		Glink.init(getActivity(), clientId, clientSecret, cafeId);
		initListeners();
	}

	public static void initGlobal(String clientId, int plugId) {
		Glink.initGlobal(getActivity(), clientId, plugId);
		initListeners();
	}

	private static void initListeners() {
		if (CafeSdk.initializedListeners) {
			return;
		}

		CafeSdk.initializedListeners = true;

		Glink.setUseVideoRecord(getActivity(), true);

		Glink.setOnSdkStartedListener(new OnSdkStartedListener() {
			@Override
			public void onSdkStarted() {
				runOnGLThread(new Runnable() {
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
				runOnGLThread(new Runnable() {
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
				runOnGLThread(new Runnable() {
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
				runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnJoined();
					}
				});
			}
		});

		Glink.setOnPostedArticleListener(new OnPostedArticleListener() {
			@Override
			public void onPostedArticle(final int menuId, final int imageCount, final int videoCount) {
				runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnPostedArticle(menuId, imageCount, videoCount);
					}
				});
			}
		});

		Glink.setOnPostedCommentListener(new OnPostedCommentListener() {
			@Override
			public void onPostedComment(final int articleId) {
				runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnPostedComment(articleId);
					}
				});
			}
		});

		Glink.setOnVotedListener(new Glink.OnVotedListener() {
			@Override
			public void onVoted(final int articleId) {
				runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnVoted(articleId);
					}
				});
			}
		});

		Glink.setOnWidgetScreenshotClickListener(new OnWidgetScreenshotClickListener() {
			@Override
			public void onScreenshotClick() {
				runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnWidgetScreenshotClick();
					}
				});
			}
		});

		Glink.setOnRecordFinishListener(new Glink.OnRecordFinishListener() {
			@Override
			public void onRecordFinished(final String uri) {
				runOnGLThread(new Runnable() {
					@Override
					public void run() {
						nativeOnRecordFinished(uri);
					}
				});
			}
		});
		
		PlugRecordManager.setOnRecordManagerListener(new OnRecordManagerListener() {
			@Override
			public void onStartRecord() {
				nativeOnStartRecord();
			}
			
			@Override
			public void onFinishRecord(String uri) {
				nativeOnFinishRecord(uri);
			}
			
			@Override
			public void onErrorRecord() {
				nativeOnErrorRecord();
			}
		});
	}

	public static void setChannelCode(String channelCode) {
		Glink.setChannelCode(channelCode);
	}

	public static String getChannelCode() {
		return Glink.getChannelCode();
	}

	public static void setThemeColor(String themeColorCSSString) {
		Glink.setThemeColor(themeColorCSSString);
	}

	public static void setThemeColor(String themeColorCSSString, String tabBackgroundColorCSSString) {
		Glink.setThemeColor(themeColorCSSString, tabBackgroundColorCSSString);
	}

	public static void startHome() {
		Glink.startHome(getActivity());
	}

	public static void startWrite() {
		Glink.startWrite(getActivity());
	}

	private static String addFileScheme(String filePath) {
		final String scheme = "file://";

		if (filePath != null && !filePath.startsWith(scheme)) {
			return scheme + filePath;
		} else {
			return filePath;
		}
	}

	public static void startImageWrite(String imageUri) {
		Glink.startImageWrite(getActivity(), addFileScheme(imageUri));
	}

	public static void startVideoWrite(String videoUri) {
		Glink.startVideoWrite(getActivity(), addFileScheme(videoUri));
	}

	public static void syncGameUserId(String gameUserId) {
		Glink.syncGameUserId(getActivity(), gameUserId);
	}

	public static boolean isShowGlink() {
		return Glink.isShowGlink(getActivity());
	}

	public static void startArticle(int articleId) {
		Glink.startArticle(getActivity(), articleId);
	}

	public static void startWidget() {
		Glink.startWidget(getActivity());
	}

	public static void stopWidget() {
		Glink.stopWidget(getActivity());
	}

	public static void showWidgetWhenUnloadSdk(boolean use) {
		Glink.showWidgetWhenUnloadSdk(getActivity(), use);
	}

	public static void setWidgetStartPosition(boolean isLeft, int heightPercentage) {
		Glink.setWidgetStartPosition(getActivity(), isLeft, heightPercentage);
	}

	public static void setUseVideoRecord(boolean use) {
		Glink.setUseVideoRecord(getActivity(), use);
	}

	public static void setUseScreenshot(boolean use) {
		Glink.setUseScreenshot(getActivity(), use);
	}
	
	public static void login() {
		NaverIdLogin.login(getActivity(), new OnLoggedInListener() {
			@Override
			public void onLoggedIn(boolean success) {
				nativeOnLoggedIn(success);
			}
		});
	}

	public static void logout() {
		NaverIdLogin.logout(getActivity());
	}

	public static boolean isLogin() {
		return NaverIdLogin.isLogin(getActivity());
	}

	public static void getProfile() {
		NaverIdLogin.getProfile(getActivity(), new OnGetProfileListener() {
			@Override
			public void onResult(String jsonString) {
				nativeOnGetProfileResult(jsonString);
			}
		});
	}

	public static void sendNewUser(String gameUserId, String market) {
		Statistics.sendNewUser(gameUserId, market);
	}

	public static void sendPayUser(String gameUserId, double pay, String productCode, String currency, String market) {
		Statistics.sendPayUser(gameUserId, pay, productCode, currency, market);
	}

	public static void showToast(final String text) {
		getActivity().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(getActivity(), text, Toast.LENGTH_LONG).show();
			}
		});
	}
	
	public static void startRecord() {
		PlugRecordManager.startRecord(getActivity());
	}

	public static void stopRecord() {
		PlugRecordManager.stopRecord();
	}
	
	private static native void nativeOnSdkStarted();

	private static native void nativeOnSdkStopped();

	private static native void nativeOnClickAppSchemeBanner(String appScheme);

	private static native void nativeOnJoined();

	private static native void nativeOnPostedArticle(int menuId, int imageCount, int videoCount);

	private static native void nativeOnPostedComment(int articleId);

	private static native void nativeOnVoted(int articleId);

	private static native void nativeOnWidgetScreenshotClick();

	private static native void nativeOnRecordFinished(String uri);

	private static native void nativeOnLoggedIn(boolean success);

	private static native void nativeOnGetProfileResult(String jsonString);
	
	private static native void nativeOnStartRecord();
	
	private static native void nativeOnErrorRecord();
	
	private static native void nativeOnFinishRecord(String uri);
}
