package com.naver.cafe;

import android.widget.Toast;
import com.naver.glink.android.sdk.Glink;
import com.naver.glink.android.sdk.Glink.OnClickAppSchemeBannerListener;
import com.naver.glink.android.sdk.Glink.OnJoinedListener;
import com.naver.glink.android.sdk.Glink.OnPostedArticleListener;
import com.naver.glink.android.sdk.Glink.OnPostedCommentListener;
import com.naver.glink.android.sdk.Glink.OnSdkStartedListener;
import com.naver.glink.android.sdk.Glink.OnSdkStoppedListener;
import com.naver.glink.android.sdk.Glink.OnWidgetScreenshotClickListener;
import com.naver.glink.android.sdk.Statistics;
import org.cocos2dx.lib.Cocos2dxActivity;

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

	public static void initGlobal(String clientId, int cafeId, String defaultCafeLangCode) {
		Glink.initGlobal(getActivity(), clientId, cafeId, defaultCafeLangCode);
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
	}

	public static void setCafeLangCode(String cafeLangCode) {
		Glink.setCafeLangCode(cafeLangCode);
	}

	public static String getCafeLangCode() {
		return Glink.getCafeLangCode();
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

	public static void startHome() {
		Glink.startHome(getActivity());
	}

	public static void startNotice() {
		Glink.startNotice(getActivity());
	}

	public static void startEvent() {
		Glink.startEvent(getActivity());
	}

	public static void startMenu(int menuId) {
		if (menuId == -1) {
			Glink.startMenu(getActivity());
		} else {
			Glink.startMenu(getActivity(), menuId);
		}
	}

	public static void startProfile() {
		Glink.startProfile(getActivity());
	}

	public static void startMore() {
		Glink.startMore(getActivity());
	}

	public static void startWrite(int menuId, String subject, String text) {
		Glink.startWrite(getActivity(), menuId, subject, text);
	}

	private static String addFileScheme(String filePath) {
		final String scheme = "file://";

		if (filePath != null && !filePath.startsWith(scheme)) {
			return scheme + filePath;
		} else {
			return filePath;
		}
	}

	public static void startImageWrite(int menuId, String subject, String text, String imageUri) {
		Glink.startImageWrite(getActivity(), menuId, subject, text, addFileScheme(imageUri));
	}

	public static void startVideoWrite(int menuId, String subject, String text, String videoUri) {
		Glink.startVideoWrite(getActivity(), menuId, subject, text, addFileScheme(videoUri));
	}

	public static void syncGameUserId(String gameUserId) {
		Glink.syncGameUserId(getActivity(), gameUserId);
	}

	public static boolean isShowGlink() {
		return Glink.isShowGlink(getActivity());
	}

	public static void showWidgetWhenUnloadSdk(boolean use) {
		Glink.showWidgetWhenUnloadSdk(getActivity(), use);
	}

	public static void stopWidget() {
		Glink.stopWidget(getActivity());
	}

	public static void setUseVideoRecord(boolean use) {
		Glink.setUseVideoRecord(getActivity(), use);
	}

	public static void sendNewUser(String gameUserId) {
		Statistics.sendNewUser(gameUserId);
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
}
