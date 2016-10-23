// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
angular.module('starter', ['ionic','starter.controllers', 'starter.services','ngCordova'])

.run(function($ionicPlatform) {
  $ionicPlatform.ready(function() {
    if(window.cordova && window.cordova.plugins.Keyboard) {
      // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
      // for form inputs)
      cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);

      // Don't remove this line unless you know what you are doing. It stops the viewport
      // from snapping when text inputs are focused. Ionic handles this internally for
      // a much nicer keyboard experience.
      cordova.plugins.Keyboard.disableScroll(true);
    }
    if(window.StatusBar) {
      StatusBar.styleDefault();
    }
  });
})
.config(function($stateProvider, $urlRouterProvider) {

  $stateProvider.state('mapview', {
    url: '/',
    templateUrl: 'templates/mapview.html',
    controller: 'MapviewController',
  })

  .state('game', {
    url: '/game',
    params: {
      selectedlevel:0
    },
    controller: 'GameController',
    templateUrl: 'templates/game.html',
  });

  

  // .state('dash.appydetail', {
  //   url: '/appydetail',
  //   params: {
  //     hotel_id: 0,
  //     distance: 0
  //   },
  //   views: {
  //     'appy-main': {
  //       templateUrl: 'templates/appydetail.html',
  //       controller: 'AppyDetailController'
  //     }
  //   }
  // });

    // if none of the above states are matched, use this as the fallback
    $urlRouterProvider.otherwise('/');
});