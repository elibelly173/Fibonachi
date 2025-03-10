//
//  GADBannerView.h
//  Google AdMob Ads SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "GADAdSize.h"
#import "GADBannerViewDelegate.h"
#import "GADInAppPurchaseDelegate.h"
#import "GADModules.h"
#import "GADRequest.h"
#import "GADRequestError.h"

/// The view that displays banner ads. A minimum implementation to get an ad
/// from within a UIViewController class is:
///
///   \code
///   // Create and setup the ad view, specifying the size and origin at {0, 0}.
///   GADBannerView *adView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
///   adView.rootViewController = self;
///   adView.adUnitID = @"ID created when registering my app";
///
///   // Place the ad view onto the screen.
///   [self.view addSubview:adView];
///   [adView release];
///
///   // Request an ad without any additional targeting information.
///   [adView loadRequest:nil];
///   \endcode
///
@interface GADBannerView : UIView

#pragma mark Initialization

/// Initializes a GADBannerView and sets it to the specified size, and specifies its placement
/// within its superview bounds. If |size| is invalid, an instance of GADBannerView is not created
/// and nil is returned instead.
- (id)initWithAdSize:(GADAdSize)size origin:(CGPoint)origin;

/// Initializes a GADBannerView and sets it to the specified size, and specifies its placement at
/// the top left of its superview. If |size| is invalid, an instance of GADBannerView is not created
/// and nil is returned instead.
- (id)initWithAdSize:(GADAdSize)size;

#pragma mark Pre-Request

/// Required value created in the AdSense website. Create a new ad unit for every unique placement
/// of an ad in your application. Set this to the ID assigned for this placement. Ad units are
/// important for targeting and stats.
/// Example values for different request types:
///
///     AdMob: a0123456789ABCD
///       DFP: /0123/ca-pub-0123456789012345/my-ad-identifier
///   AdSense: ca-mb-app-pub-0123456789012345/my-ad-identifier
/// Mediation: AB123456789ABCDE
@property(nonatomic, copy) NSString *adUnitID;

/// Required reference to the current root view controller. For example the root view controller in
/// tab-based application would be the UITabViewController.
@property(nonatomic, weak) UIViewController *rootViewController;

/// Required to set this banner view to a proper size. Never create your own GADAdSize directly. Use
/// one of the predefined standard ad sizes (such as kGADAdSizeBanner), or create one using the
/// GADAdSizeFromCGSize method. If not using mediation, then changing the adSize after an ad has
/// been shown will cause a new request (for an ad of the new size) to be sent. If using mediation,
/// then a new request may not be sent.
@property(nonatomic, assign) GADAdSize adSize;

/// Optional delegate object that receives state change notifications from this GADBannerView.
/// Typically this is a UIViewController, however, if you are unfamiliar with the delegate pattern
/// it is recommended you subclass this GADBannerView and make it the delegate. That avoids any
/// chance of your application crashing if you forget to nil out the delegate. For example:
///
///   \code
///   @interface MyAdView : GADBannerView <GADBannerViewDelegate>
///   @end
///
///   @implementation MyAdView
///   - (id)initWithFrame:(CGRect)frame {
///     self = [super initWithFrame:frame];
///     if (self) {
///       self.delegate = self;
///     }
///     return self;
///   }
///
///   - (void)dealloc {
///     self.delegate = nil;
///     [super dealloc];
///   }
///
///   @end
///   \endcode
@property(nonatomic, weak) NSObject<GADBannerViewDelegate> *delegate;

/// Optional delegate object that receives In-App Purchase (IAP) notifications from this
/// GADBannerView. Remember to nil the delegate before deallocating this object.
@property(nonatomic, weak) id<GADInAppPurchaseDelegate> inAppPurchaseDelegate;

#pragma mark Making an Ad Request

/// Makes an ad request. Additional targeting options can be supplied with a request object. Refresh
/// the ad by calling this method again.
- (void)loadRequest:(GADRequest *)request;

#pragma mark Ad Request

/// Indicates if the currently displayed ad (or most recent failure) was a result of auto refreshing
/// as specified on server. This property is set to NO after each loadRequest: method.
@property(nonatomic, readonly, assign) BOOL hasAutoRefreshed;

#pragma mark Mediation

/// The underlying ad view of the mediated ad network. You may use this to find out the actual
/// size of the ad and adjust GADBannerView to fit the underlying ad view.
@property(nonatomic, readonly, weak) UIView *mediatedAdView;

/// The ad network class name that fetched the current ad. Returns nil while the latest ad request
/// is in progress or if the latest ad request failed. For both standard and mediated Google AdMob
/// ads, this method returns @"GADMAdapterGoogleAdMobAds". For ads fetched via mediation custom
/// events, this method returns @"GADMAdapterCustomEvents".
@property(nonatomic, readonly, weak) NSString *adNetworkClassName;

@end
