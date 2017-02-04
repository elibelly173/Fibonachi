angular.module('starter.controllers', ['ionic','ngStorage','ngLoad', 'ngAnimate', 'ngSanitize', 'ionic-native-transitions'])
.controller('StartviewController', function($scope, $stateParams, $state,$timeout, $ionicNativeTransitions, $window) {
  $scope.mapflag=false;

  var devicewidth=$window.innerWidth; 
  var deviceheight=$window.innerHeight;
  if((devicewidth/deviceheight) > (1334/750)){
    $scope.videoDeviceFlag = true;
  } else {
    $scope.videoDeviceFlag = false;
  }

    $scope.startclcik = function(){
      //in android "playimage"
      $scope.videoPreviewFlag= true;
      $timeout(function() {
        $scope.videoflag= true;
        }, 800);
      
      $timeout(function() {
        if(!$scope.mapflag){
          $scope.gotomapview();
        }
        
      }, 13000);
    }

    $scope.gotomapview = function(){
      $scope.mapflag=true;
      // $state.go('mapview');
      $ionicNativeTransitions.stateGo('mapview', {}, {}, {
        "type": "fade",
        "duration": 1000 // in milliseconds (ms), default 400 
      });
    }
})
.controller('CutscreenviewController', function($scope, $stateParams, $state, $timeout) {
  // var video = document.getElementById("videoplay");
  // $scope.gotomaview = function(){
  //   // video.pause();
  //   // video.currentTime = 0;
  //     $state.go('mapview');
  //   }


  //   $timeout(function() {
  //       // video.pause();
  //       // video.currentTime = 0;
  //       $state.go('mapview');
        
  //   }, 13000);
})


.controller('MapviewController', function($ionicNativeTransitions, $scope, $stateParams, $state, $ionicScrollDelegate,$timeout, $window, $rootScope, $localStorage, $ionicPopup) {

	$timeout(function() {
        var scrollView = $ionicScrollDelegate.$getByHandle('page1');
        scrollView.scrollBottom(false);
        
    }, 10);
    var devicewidth=$window.innerWidth;
    
    var deviceheight=$window.innerHeight;

    var vh=deviceheight/100;
    var vw=devicewidth/100;
    $rootScope.vh = vh;
    $rootScope.vw = vw;
    var ratiovhvw=vh/vw;
    var ratioangle=180/3.14;
    var alpha1=Math.atan(7*ratiovhvw/25);
    var length= (7*vh/Math.asin(alpha1)).toFixed(1);
    $rootScope.vw= vw;
    $rootScope.vh= vh;
    $rootScope.length=length+'px';
    $rootScope.alpha1=alpha1*180/3.14;
    $rootScope.alpha2=360-$rootScope.alpha1;

    // if not click key, value is 0,
    // if only clicked one, 1
    // if clicked 2+ or enter, 2
    $localStorage.keyclickflag='0';
    // if not click enter, value is 0,
    // if only clicked one, 1
    $localStorage.enterclickflag='0';
    $localStorage.swipeclickflag='0';
    $localStorage.entershowflag='0';
    $localStorage.swipeshowflag='0';

    if(!$localStorage.completedlevel){
      $localStorage.completedlevel = 1;
    }

    $scope.levelclickflag = false;
    $scope.mapScrollFlag =true;

    $scope.mapbarlists=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
      28,29,30,31,32];


    $rootScope.levelTitleList = [{id: 1, number:20, time: 40}, {id: 2, number:20, time: 40}, {id: 3, number:20, time: 40}, 
          {id: 4, number:20, time: 40}, {id: 5, number:20, time: 40}, {id: 6, number:20, time: 45}, {id: 7, number:20, time: 25}, 
          {id: 8, number:20, time: 35}, {id: 9, number:20, time: 45}, {id: 10, number:20, time: 45}, {id: 11, number:20, time: 40}, 
          {id: 12, number:20, time: 40}, {id: 13, number:20, time: 40}, {id: 14, number:20, time: 40}, {id: 15, number:20, time: 30}, 
          {id: 16, number:20, time: 40}, {id: 17, number:20, time: 50}, {id: 18, number:20, time: 50}, {id: 19, number:20, time: 50},
          {id: 20, number:20, time: 50}, {id: 21, number:20, time: 40}, {id: 22, number:20, time: 40}, {id: 23, number:20, time: 40},
          {id: 24, number:20, time: 40}, {id: 25, number:20, time: 45}, {id: 26, number:20, time: 50}, {id: 27, number:20, time: 55},
          {id: 28, number:20, time: 55}, {id: 29, number:20, time: 55}, {id: 30, number:20, time: 40}, {id: 31, number:20, time: 40},
          {id: 32, number:20, time: 50}];

    $scope.onPopupClose = function() {

      angular.element("#real-explain").animate({left:10+'%'},150, function(){
          angular.element("#real-explain").animate({left:-100+'%'}, 300, function(){
              
          });
      });
      $timeout(function() {
        $scope.levelclickflag = false;
      }, 500);
    }    


    $scope.levelclick=function(e){
      
      // if(e <= Number($localStorage.completedlevel)){
      //   $rootScope.level=e;
      //   $localStorage.level=e;
      //   $state.go('game', {selectedlevel: e});
      // } else {
      //    var alertPopup = $ionicPopup.alert({
      //     title: 'Warning!',
      //     template: 'Please select level less than '+$localStorage.completedlevel
      //    });
      // }

      
      $rootScope.level=e;
      $localStorage.levelTime=$rootScope.levelTitleList[e-1].time;
      $localStorage.level=e;
      $scope.levelclickflag = true;
      $scope.mapScrollFlag =false;

      $timeout(function(){
        angular.element("#real-explain").animate({left:-10+'%'},300, function(){
          angular.element("#real-explain").animate({left:0+'%'}, 150);
        });      
      }, 100);
        
        // // $state.go('game', {selectedlevel: e});
        // $ionicNativeTransitions.stateGo('game', {}, {}, {
        //   "type": "slide",
        //   "direction": "left", // 'left|right|up|down', default 'left' (which is like 'next') 
        //   "duration": 500, // in milliseconds (ms), default 400 
        // });
      

    }

    $scope.gotoGameview = function() {


      angular.element("#real-explain").animate({left:10+'%'},150, function(){
          angular.element("#real-explain").animate({left:-100+'%'}, 300, function(){
              $scope.levelclickflag = false;
              $ionicNativeTransitions.stateGo('game', {}, {}, {
                "type": "slide",
                "direction": "left", // 'left|right|up|down', default 'left' (which is like 'next') 
                "duration": 500, // in milliseconds (ms), default 400 
              });
          });
      });
    }

    $scope.$on("$ionicView.enter", function(event, data){

      $rootScope.completedlevel = $localStorage.completedlevel;
      // $rootScope.completedlevel = 32;
      // if($localStorage.completedlevel ){
          if(Number($localStorage.completedlevel) > Number($localStorage.level)){


            var top = angular.element(document.querySelector("#mapcircle"+$localStorage.completedlevel)).prop('offsetTop');
            var left = angular.element(document.querySelector("#mapcircle"+$localStorage.completedlevel)).prop('offsetLeft');
            console.log("completedlevel="+$localStorage.completedlevel + " top="+ top+ " left="+ left);
            angular.element("#locationimg").animate({left:left+'px', top : top - 11*vw +'px'},2000,'linear');
          } else if(Number($localStorage.completedlevel) == 1) {
            var top = angular.element(document.querySelector("#mapcircle1")).prop('offsetTop');
            var left = angular.element(document.querySelector("#mapcircle1")).prop('offsetLeft');
            
            angular.element("#locationimg").animate({left:left+'px', top : top - 11*vw +'px'},500,'linear');
          }
        // }
        // else {
        //   var top = angular.element(document.querySelector("#mapcircle1")).prop('offsetTop');
        //   var left = angular.element(document.querySelector("#mapcircle1")).prop('offsetLeft');
         
        //    angular.element("#locationimg").animate({left:left+'px', top : top - 11*vw +'px'},2000,'linear');
        // }
    });

    $scope.animationfoot = function(){
       
      var footcss={};
      // if(Number($localStorage.completedlevel) ==1 ){
      //   var top = angular.element(document.querySelector("#mapcircle1")).prop('offsetTop');
      //   var left = angular.element(document.querySelector("#mapcircle1")).prop('offsetLeft');
      // }

      // footcss ={
      //   'top' : top - 11 * vw + 'px',
      //   'left': left + 'px'
      // }
        
     
        
      
      return footcss;
    }
    
 

    // $scope.scrollmap=function(){
    // 	if($ionicScrollDelegate.getScrollPosition().top<50){
    // 		// $(".page1").show();
    // 	 //  	var height=$(".page1").height();
    	 
    // 	 //  	$ionicScrollDelegate.scrollTo(0,height,false);

    // 	}
    
    // }
	 
})

.controller('ReportController', function($scope, $stateParams, $state, $timeout, $rootScope, $ionicNativeTransitions, $ionicHistory, $localStorage) {
  // $scope.starlists=[1,2,3,4];

  // $ionicHistory.clearHistory();
  $scope.speedlists = ['img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
  $scope.accuracylists = ['img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];


  if($rootScope.levelspeed == 100){
    $scope.speedlists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png'];
  } else if($rootScope.levelspeed > 75 && $rootScope.levelspeed <= 99){
    $scope.speedlists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png', 'img/report/outline.png'];
  } else if($rootScope.levelspeed > 50 && $rootScope.levelspeed <= 74){
    $scope.speedlists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/outline.png', 'img/report/outline.png'];
  } else if($rootScope.levelspeed > 0 && $rootScope.levelspeed <= 49){
    $scope.speedlists = ['img/report/report_star.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
  }

  if($rootScope.levelaccuracy == 100){
    $scope.accuracylists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png'];
  } else if($rootScope.levelaccuracy > 75 && $rootScope.levelaccuracy <= 99){
    $scope.accuracylists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png', 'img/report/outline.png'];
  } else if($rootScope.levelaccuracy > 50 && $rootScope.levelaccuracy <= 74){
    $scope.accuracylists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/outline.png', 'img/report/outline.png'];
  } else if($rootScope.levelaccuracy > 0 && $rootScope.levelaccuracy <= 49){
    $scope.accuracylists = ['img/report/report_star.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
  }


  $scope.backfunc = function (){
    $ionicNativeTransitions.stateGo('game', {}, {}, {
          "type": "slide",
          "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
          "duration": 500, // in milliseconds (ms), default 400 
        });
  }
  $scope.continuefunc = function (){
    $rootScope.level +=1;
    $localStorage.level = $rootScope.level;
    $ionicNativeTransitions.stateGo('game', {}, {}, {
          "type": "slide",
          "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
          "duration": 500, // in milliseconds (ms), default 400 
        });
  }
  $scope.exitfunc = function (){
    $ionicNativeTransitions.stateGo('mapview', {}, {}, {
          "type": "slide",
          "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
          "duration": 500, // in milliseconds (ms), default 400 
        });
  }



})
.controller('GameController', function($ionicHistory, $timeout, $ionicNativeTransitions, $scope, $stateParams, $state, $ionicScrollDelegate, $timeout, $interval, $cordovaVibration, $window, $rootScope, $animate, $localStorage,
           problemservice, problemservice17, problemservice18, problemservice19, problemservice20, problemservice21, problemservice22,
           problemservice23, problemservice24, problemservice25, problemservice26, problemservice27, problemservice30, problemservice31, problemservice32) {
   $scope.list1s=[0,1,2,3,4,5,6];
   $scope.list2s=[1,2,3,4];
   $scope.listlevel20 = [1,2];
   $scope.listbutton1s=[1,3,5,7,9];
   $scope.listbutton2s=[2,4,6,8,0];
   $scope.listproblems=[0,1,2,3,4,5,6,7];
   $scope.listbuttons=[1,2,3,4,5,6,7,8,9,0];
   
   $scope.arrowlists=[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
      28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49];
    
   // $ionicNativeTransitions.enable(true);
    var firstclickedflag = false; //  flag for level 28

       var touchposx = 0;
       var touchposy = 0;
       var touchstartflag = false;


       var correctcount=0;
       var compareproblem=0;
       var levelerrorcount = 0;

       var stackSize=0;

       var problemtime= 3000;
       
       // list of answer
       var solutionQueue = [];

       //In level 24 ~ 27 when denomenator is equal to 1, we should remove denomenator from fraction.
       $scope.denometor111 = [];

       var mytimeout, myproblemtime;
       var keytime, entertime, swipetime;
       var count=0;
       var nowdate= new Date();
       var nowtime= nowdate.getTime();

       $scope.starlists = [];


       $scope.timer=0;
       $scope.score=0;
       $scope.paused = true;
       $scope.answer='';
       $scope.addop=1;
       // $scope.level= $stateParams.selectedlevel;
       $scope.level = $rootScope.level;
       $scope.axisflag=0;

       $scope.entershowflag='0';
       $scope.swipeshowflag='0';
       $scope.fractionflag = false;
       $scope.addflag = false;
       $scope.rightanswerflag = false;
       $scope.deciamlflag = false;
       $scope.cloud25flag = false;
       $scope.bubbleAnswerFlag = false;


       $scope.fiboballFlag = false;

    //  flags for fraction design effect (level 26)
        // when clicked level 26, true
        $scope.level26flag = false;
        $scope.level20flag = false;
        // On level 26, it is for inputing obvious factor
        $scope.questionboxflag = [];
        // On level 26, when click answerbox, you can input there using keyboard
        $scope.answerboxflag = [];
        // On level 26, init value of answerbox
        $scope.level26value = [1, 1, 1, 1, 1];
        // on level26, if click answerbox, you can't input answer
        $scope.keyenterclickedflag = true;
        $scope.decimalFlag = false;

       $scope.problemorder = 0;

       switch($scope.level){
          case 20:
            $scope.level20flag=true;
            
            break;
          case 21:
            $scope.axisflag=1;
            $scope.bubbleAnswerFlag = true;
            break;
          case 22:
            $scope.axisflag=2;
            $scope.bubbleAnswerFlag = true;
            break;
          case 23: case 31:
            $scope.axisflag=3;
            break;
          case 25:
            $scope.cloud25flag=true;
            $scope.level26flag=true;
            break;
          case 26: case 27:
            $scope.level26flag=true;
            break;
          case 28: case 29:
            $scope.level26flag=true;
            $scope.level28flag=true;
            break;
          case 30: case 32:
            $scope.deciamlflag = true;
            break;
       }

       if($scope.level>20){
        $scope.addop=0;
       }
       if($scope.level>=20 && $scope.level<31){
        $scope.fractionflag=true;
       }

       if($scope.level>=12){
        $scope.addflag=true;
       }

       // list of problems
       $scope.arryproblems=[];
       $scope.insteadarryproblems=[];
       


   $scope.$on("$ionicView.loaded",  function(){      
      








      $scope.paused=true;
      $scope.entershowflag=$localStorage.entershowflag;
      $scope.swipeshowflag=$localStorage.swipeshowflag;

      
      
      
      mytimeout = $timeout($scope.onTimeout, 1000);
      if($localStorage.pauseedflag == '1' && $localStorage.pauseedlevel == $localStorage.level){
        $scope.timer=$localStorage.timer;
        $localStorage.pauseedflag='0';
        $scope.arryproblems = $localStorage.arryproblems;
        $scope.problemorder = Number($localStorage.problemorder);
        $scope.insteadarryproblems = $localStorage.insteadarryproblems;
        solutionQueue = $localStorage.solutionQueue;
        $scope.denometor111 = $localStorage.denometor111;
        correctcount = Number($localStorage.correctcount);
        $scope.question = $scope.arryproblems[0];
        compareproblem=$localStorage.compareproblem;
        $scope.score=$localStorage.score;
        for(var ii=0; ii<correctcount; ii++){
          $scope.starlists.push(ii+1);
        }
      } else{
        
        
        makeproblem();
        makeproblem();
      }
    });



  $scope.touchstart = function(e) {
    e.preventDefault();
    var touch = e.originalEvent.changedTouches[0] || e.originalEvent.touches[0] || e.touches[0] || e.changedTouches[0];
     touchposx = touch.pageX;
     touchposy = touch.pageY;
     if(touchposx > 30*$rootScope.vw) {
        console.log("aaa");
       touchstartflag = true;
     }
   
  }
  $scope.touchend = function(e) {
    e.preventDefault();
    var touch = e.originalEvent.changedTouches[0] || e.originalEvent.touches[0] || e.touches[0] || e.changedTouches[0];
    var x = touch.pageX;
    var y = touch.pageY;
    if(touchstartflag && x > 30 * $rootScope.vw) {
      if(Math.abs(y - touchposy) > 3 * $rootScope.vw) {
        // $scope.arryproblems[$scope.problemorder] = $scope.insteadarryproblems[$scope.problemorder];
        angular.element("#problem" + compareproblem + " .bottomfracproblem").animate({top : 0 +'px'},200,'linear');
        angular.element("#problem" + compareproblem + " .topfracproblem").animate({top : 4.4*$rootScope.vw +'px'},200,'linear');
        touchstartflag = false;
        firstclickedflag = true;
      }
    }
  }


  $scope.onTouchDotStart = function(e) {
    e.preventDefault();
    var touch = e.originalEvent.changedTouches[0] || e.originalEvent.touches[0] || e.touches[0] || e.changedTouches[0];
     var x = touch.pageX;
     var y = touch.pageY;
     
   
  }
  $scope.onTouchDotEnd = function(e) {
    e.preventDefault();
    var touch = e.originalEvent.changedTouches[0] || e.originalEvent.touches[0] || e.touches[0] || e.changedTouches[0];
    var x = touch.pageX;
    var y = touch.pageY;
    
  }

  $scope.onTouchDotMove = function(e) {
    e.preventDefault();
    var touch = e.originalEvent.changedTouches[0] || e.originalEvent.touches[0] || e.touches[0] || e.changedTouches[0];
    var x = touch.pageX;
    var y = touch.pageY;
    console.log("touch-move"+x);
    
  }




   $scope.onTimerColor = function (){
      if($scope.timer<($rootScope.levelTitleList[$rootScope.level - 1].time -10)){
        return {"color": 'green'};
      } 
      // else if( ($rootScope.levelTitleList[$rootScope.level - 1].time -10) < $scope.timer<$rootScope.levelTitleList[$rootScope.level - 1].time) {
      //   return {"color": "yellow"};
      // } 
      else if( $rootScope.levelTitleList[$rootScope.level - 1].time <= $scope.timer) {
        return {"color": "yellow"};
      } 

      // if($scope.timer<5){
      //   return {"color": 'green'};
      // } 
      // else if( 5 <= $scope.timer<10) {
      //   return {"color": "yellow"};
      // } 
      
   }

   
    $scope.onTimeout = function() {
      
      $scope.timer++;

      // console.log($rootScope.levelTitleList[$rootScope.level - 1].time);
      // console.log($scope.timer);
      if($scope.timer<($rootScope.levelTitleList[$rootScope.level - 1].time -10)){
        $scope.timer_color = "greencolor";
        // console.log("greencolor");
      } else if( ($rootScope.levelTitleList[$rootScope.level - 1].time - 10) <= $scope.timer && $scope.timer < $rootScope.levelTitleList[$rootScope.level - 1].time) {
        $scope.timer_color = "yellowcolor";
        
      } else if( $rootScope.levelTitleList[$rootScope.level - 1].time <= $scope.timer) {
        $scope.timer_color = "redcolor";
        
      } 

      
      

      // if($rootScope.levelTitleList[$rootScope.level - 1].time > $scope.timer){
      //   mytimeout = $timeout($scope.onTimeout, 1000);
       
      // } else {
      //    reportshowfunc('failed');
      // }
      
     if($scope.paused){
         mytimeout = $timeout($scope.onTimeout, 1000);
     }

    };
    // currently, no need
    $scope.onTimeoutproblem = function() {
        
        if(stackSize<8){
          makeproblem();
        }else{
          
          stopTimer();
        }
        
      
      
     if($scope.paused){
         myproblemtime = $timeout($scope.onTimeoutproblem, problemtime);
     }

    };

    // for starting enter animation and swipe animation
    var keytimefunc = function(){
      if($localStorage.enterclickflag == '0'){
        //$rootScope.
        $scope.entershowflag='1';
      } else if($localStorage.swipeclickflag == '0' && $scope.entershowflag == '2'){
        $scope.swipeshowflag='1';
      }
    }

    // showing enter animation

    var entertimefunc = function(){
      if($scope.entershowflag=='1'){
        $scope.entershowflag='2';
      } else {
        $scope.entershowflag='0';
      }
      
    }


    // showing and removing swipe animation
    var swipetimefunc = function(){
      $scope.swipeshowflag='0';
    }

    // currently, no need
    var stopTimer= function(){
      stackSize=0;
          $scope.arryproblems=[];
          $scope.insteadarryproblems=[];
          $timeout.cancel(mytimeout);
          $timeout.cancel(myproblemtime);
          $scope.paused = false;
          $ionicNativeTransitions.stateGo('mapview', {}, {}, {
            "type": "slide",
            "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
            "duration": 500, // in milliseconds (ms), default 400 
          });
    };
    

    // making as level
    var makeproblem= function(){
      var problem, insteadpro, insteadpro1;
      if($scope.level<17){
        problem = JSON.parse(problemservice.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.oppar1+problem.second+problem.oppar2;
      } else if($scope.level==17){
        problem = JSON.parse(problemservice17.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.second+problem.op+problem.third;
      }else if($scope.level==18){
        problem = JSON.parse(problemservice18.generateProblem($scope.level));
        
        insteadpro=''+problem.first+'+'+problem.second+'+'+problem.third;
      }else if($scope.level==19){
        problem = JSON.parse(problemservice19.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.second+problem.op1+problem.third ;
      }else if($scope.level==20){
        problem = JSON.parse(problemservice20.generateProblem($scope.level));
        
        insteadpro = "<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>";
      }else if($scope.level==21){
        problem = JSON.parse(problemservice21.generateProblem($scope.level));
        
        insteadpro = "<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>";
      } else if($scope.level==22){
        problem = JSON.parse(problemservice22.generateProblem($scope.level));
       
        insteadpro =problem.op + "<div class='frac'  class='topfrac'><span>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>";
      }
      else if($scope.level==23){
        problem = JSON.parse(problemservice23.generateProblem($scope.level));
        insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>"+"<div class='compareop'>___</div>"+"<div class='frac'><span class='topfrac'>1</span><div class='hr-line'></div><span class='bottom'>2</span></div>";
      } else if($scope.level==24){
        problem = JSON.parse(problemservice24.generateProblem($scope.level));

        if(problem.second == 1){
          insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        } else {
          insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        }
        
      }
      else if($scope.level==25){
        problem = JSON.parse(problemservice25.generateProblem($scope.level));
        if(problem.second == 1){
          insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        } else {
          insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        }          
        
      }
      else if($scope.level==26){
        problem = JSON.parse(problemservice26.generateProblem($scope.level));          
        if(problem.second == 1){
          insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        } else {
          insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        }         
      }
      else if($scope.level==27){
        problem = JSON.parse(problemservice27.generateProblem($scope.level));          
        if(problem.second == 1){
          insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        } else {
          insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        }         
      }
      else if($scope.level==28){

            var select26 = Math.floor(Math.random() * (1 + 1)) + 0;
            if(select26){
              problem = JSON.parse(problemservice27.generateProblem(27));
            } else {
              problem = JSON.parse(problemservice26.generateProblem(26));
            }
            
         
           if(problem.second == 1){
              insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
            } else {
              insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
            }         
      }
      else if($scope.level==29){

            var selectlevel = Math.floor(Math.random() * (29 - 23)) + 24;
            
              problem = JSON.parse(problemservice27.generateProblem($scope.level));
                     
           insteadpro ="<div class='frac'><span class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" + "<div class='frac-op'>&divide</div>"  + "<div class='frac'><span class='topfrac topfracproblem'>"+problem.forth+"</span><div class='hr-line'></div><span class='bottom bottomfracproblem'>"+problem.third+"</span></div>";
           switch(selectlevel){
              case 24:
                problem = JSON.parse(problemservice24.generateProblem(24));
                if(problem.second == 1){
                  insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
                } else {
                  insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
                }         
                break;
              case 25:
                problem = JSON.parse(problemservice25.generateProblem(25));          
                if(problem.second == 1){
                  insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
                } else {
                  insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
                }         
                break;
              case 26:
                problem = JSON.parse(problemservice26.generateProblem(26));          
                if(problem.second == 1){
                  insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
                } else {
                  insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
                }         
                break;
              case 27:
                problem = JSON.parse(problemservice27.generateProblem(27));          
                if(problem.second == 1){
          insteadpro ="<div class='frac_1'>"+problem.first+"</div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        } else {
          insteadpro ="<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" +problem.op+ "<div class='frac'><span class='topfrac'>"+problem.third+"</span><div class='hr-line'></div><span class='bottom'>"+problem.forth+"</span></div>";
        }         
                break;
              case 28:
                problem = JSON.parse(problemservice27.generateProblem(27));
                insteadpro ="<div class='frac'><span class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" + "<div class='frac-op'>&divide</div>"  + "<div class='frac'><span class='topfrac topfracproblem'>"+problem.forth+"</span><div class='hr-line'></div><span class='bottom bottomfracproblem'>"+problem.third+"</span></div>";
                break;
              case 29:
                problem = JSON.parse(problemservice26.generateProblem(26));
                insteadpro ="<div class='frac'><span class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" + "<div class='frac-op'>&divide</div>"  + "<div class='frac'><span class='topfrac topfracproblem'>"+problem.forth+"</span><div class='hr-line'></div><span class='bottom bottomfracproblem'>"+problem.third+"</span></div>";
                break;
           }
      }else if($scope.level==30){
        problem = JSON.parse(problemservice30.generateProblem($scope.level));
         insteadpro = "<div class='normalfrac'><div class='top-numerator'><span>"+problem.first+"</span></div><div class='bottom-denominator'><span>"+problem.second+"</span></div></div>";
        // insteadpro = "<div class='frac'><span  class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>";
      }
      else if($scope.level==31){
        problem = JSON.parse(problemservice31.generateProblem($scope.level));
        insteadpro=''+problem.first+problem.op+problem.second;
      }else if($scope.level==32){
        problem = JSON.parse(problemservice32.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.second;
      }

        console.log("answer= " + problem.answer );
        solutionQueue.push(problem.answer);
        $scope.denometor111.push(problem.second);
        $scope.arryproblems.push(insteadpro);
        
        if($scope.arryproblems.length == 1) {
         $scope.question= $scope.arryproblems[0];
        }
       
       stackSize++;
    }
    
    // function for level 26
    // To input answer boxes, click each answer box
    
    $scope.answerboxclicked = function(order) {

        $scope.clickedorder = order;
        $scope.answerboxflag = [];
        $scope.level26value[order] = '';
        $scope.keyenterclickedflag = false;
        if(!$scope.answerboxflag[order]){
          $scope.answerboxflag[order] = true;
        }
       
    }

    // when click question box, answer box and cross line appear on level 26
    
    $scope.questionboxclicked = function (order) {

      if($scope.level == 28 && !firstclickedflag){
        // firstclickedflag = true;
        // angular.element("#problem" + compareproblem + " .bottomfracproblem").animate({top : 0 +'px'},200,'linear');
        // angular.element("#problem" + compareproblem + " .topfracproblem").animate({top : 4.4*$rootScope.vw +'px'},200,'linear');
      } else {
          $scope.clickedorder = order;
      
          if(!$scope.questionboxflag[order]){
            $scope.questionboxflag[order] = true;
          } else {
            $scope.questionboxflag[order] = false;
          }

          $scope.answerboxflag = [];
          $scope.level26value[order] = '';
          $scope.keyenterclickedflag = false;
          if(!$scope.answerboxflag[order]){
              $scope.answerboxflag[order] = true;
          }
      } 
     
    }


    $scope.signboxclicked = function () {
      angular.element("#problem" + compareproblem + " .frac-op").html('x');

    }


    // problem animation
   $scope.animation= function(e){
    var animcss={};
    if( e == compareproblem){
      if($scope.level==25){
        animcss= {
          'top': 83*$rootScope.vh - 21*$rootScope.vw,
          'left': '31vw',
          'z-index': 52
        };
      } else if($scope.level !=25 && $scope.fractionflag){
        animcss= {
          'top': 83*$rootScope.vh - 21*$rootScope.vw,
          'left': '31vw',
          'z-index': 52,
          'transition': 'all 700ms',
          'transition-timing-function': 'linear'
        };
      } else {
        animcss= {
          'top': 83*$rootScope.vh - 17.5*$rootScope.vw,
          'left': '31vw',
          'z-index': 52,
          'transition': 'all 700ms',
          'transition-timing-function': 'linear'
        };
      }
      
    } else if(e - compareproblem ==1){
      if($scope.level==25){
        var animcss={
          'display': 'none'
        };
      } else {
        var animcss={
          'top': 9*$rootScope.vh + 6*$rootScope.vw,
          'left': '11vw',
          'z-index': 51,
          '-webkit-animation': 'animationtop1',
          'animation': 'animationtop1',
          'animation-duration': '500ms',
          '-webkit-animation-duration': '500ms'
        };
      }
      
    } else {
       var animcss={
        'display': 'none'
      };
    }
    
    return animcss;
   }

   // 
    
    $scope.clikedpause= function(){

      $localStorage.entershowflag = $scope.entershowflag;
      $localStorage.swipeshowflag = $scope.swipeshowflag;


      $localStorage.pauseedflag='1';
      $localStorage.pauseedlevel=$localStorage.level;
      $localStorage.correctcount=correctcount;
      $localStorage.solutionQueue=solutionQueue;
      $localStorage.denometor111 = $scope.denometor111;
      $localStorage.arryproblems=$scope.arryproblems;
      $localStorage.problemorder=$scope.problemorder;
      $localStorage.insteadarryproblems=$scope.insteadarryproblems;
      $localStorage.timer=$scope.timer;
      $localStorage.compareproblem=compareproblem;
      $localStorage.score=$scope.score;
      // $state.go('mapview');
      $ionicNativeTransitions.stateGo('mapview', {}, {}, {
        "type": "slide",
        "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
        "duration": 500, // in milliseconds (ms), default 400 
      });

    }

    $scope.divideflag = false;

    // insteadpro ="<div class='frac'><span class='topfrac'>"+problem.first+"</span><div class='hr-line'></div><span class='bottom'>"+problem.second+"</span></div>" + "<div class='frac-op'>&divide</div>"  + "<div class='frac'><span class='topfrac topfracproblem'>"+problem.forth+"</span><div class='hr-line'></div><span class='bottom bottomfracproblem'>"+problem.third+"</span></div>";

    $scope.keydivideclick= function(){
      if($scope.divideflag == false){
        $scope.divideflag = true;
        $scope.insteadanswer = '';
        // $scope.insteadanswer= "<div class='normalfrac'><div class='top-numerator'><span>"+$scope.answer+"</span></div><div class='bottom-denominator'><span>"+"</span></div></div>";
        $scope.insteadanswer="<div class='frac'><span class='topfrac'>"+$scope.answer+"</span><div class='hr-line'></div><span class='bottom'>"+"</span></div>";
        $scope.answer += '/';
      }
      
    }

    $scope.keyclick=function(e){
      // if there is clicked answer box, can input there
      if($scope.answerboxflag[$scope.clickedorder] == true){
        
          $scope.level26value[$scope.clickedorder] +=  e;
          $scope.answerboxflag = [];
          $scope.keyenterclickedflag = true;
       
      }  else{

        // when input answer
        // 
        if($localStorage.keyclickflag == '0' && $localStorage.enterclickflag == '0'){
          $localStorage.keyclickflag = '1';
          keytime = $timeout(keytimefunc, 5000);
        } else if($scope.entershowflag == '2' && $localStorage.swipeclickflag == '0'){
          swipetime = $timeout(keytimefunc, 5000);
          $localStorage.keyclickflag ='2';
        } else{
          $localStorage.keyclickflag ='2';
        }

        $scope.answer += e;

        if($scope.divideflag){
          var value = $scope.answer.split("/");
          $scope.insteadanswer = '';
          $scope.insteadanswer= "<div class='normalfrac'><div class='top-numerator'><span>"+value[0]+"</span></div><div class='bottom-denominator'><span>"+value[1]+"</span></div></div>";
          // $scope.insteadanswer="<div class='frac'><span class='topfrac'>"+value[0]+"</span><div class='hr-line'></div><span class='bottom'>"+value[1]+"</span></div>";
        } else {
          $scope.insteadanswer = $scope.answer;
        }
      }
        
         
    }


    $scope.keyaddclick=function(){
      $scope.divideflag = false;
       if($scope.answer.indexOf('-')>-1){
        var strans= $scope.answer.split("-");
          $scope.answer = strans[1];
       } else{
            $scope.answer = '-' + $scope.answer;
       }

       $scope.insteadanswer= $scope.answer;
    }

    // $scope.keydecimalclick = function(){
    //   if(!$scope.decimalFlag) {
    //     $scope.answer +='.';
    //     $scope.insteadanswer = $scope.answer;
    //   }
    // }

    $scope.keydecimalclick = function(){
      if(!$scope.decimalFlag) {
        // $scope.answer +='<span>.</span>';
        $scope.answer +='.';
        $scope.insteadanswer = $scope.answer;
      }
    }

    $scope.arrowclick= function(e){

      if(solutionQueue[0] <= (e+5) && solutionQueue[0] >= (e - 5)){

        rightanswer();
      }
    }
    $scope.compareclick= function(e){
      if(e == solutionQueue[0]){
        rightanswer();
      }
    }

    $scope.enter= function() {
      if($scope.keyenterclickedflag){
        $scope.divideflag = false;
        $scope.insteadanswer = '';
         $scope.decimalFlag = false;
        if($localStorage.enterclickflag == '0'){
            $localStorage.enterclickflag = '1';
            entertimefunc();
        } 
        

          if($scope.answer==solutionQueue[0]){
            rightanswer();
          }else{
            wronganswer();
          }
        
          $scope.answer = '';
      } else {
        $scope.keyenterclickedflag = true;
        $scope.answerboxflag = [];
      }
    }


    $scope.swipefunc= function(){
      $scope.divideflag = false;
      $scope.insteadanswer = '';
      $scope.answer = '';
      if($localStorage.swipeclickflag == '0'){
          $localStorage.swipeclickflag = '1';
          swipetimefunc();
        } 
    }
    var animimagecount=1;
    $scope.achiimage = "img/achianim/achiAnim1.png";
    var countUp = function() {
        animimagecount +=1;
        $scope.achiimage = "img/achianim/achiAnim"+animimagecount+".png";
        if(animimagecount <10){
          $timeout(countUp, 70);
        } else {
          animimagecount = 1;
        }
        
    }



    var fiboAnimCount=1;
    $scope.fiboimage = "img/fiboanim/fiboanim1.png";
    var countFiboUp = function() {
        fiboAnimCount +=1;
        $scope.fiboimage = "img/fiboanim/fiboanim"+fiboAnimCount+".png";
        if(fiboAnimCount <10){
          $timeout(countFiboUp, 50);
        } else {
          fiboAnimCount = 1;
        }
        
    }

    var rightanswer= function(){
      // level26 flags initialize
        $scope.problemorder += 1;
        $scope.questionboxflag=[];
        $scope.answerboxflag = [];

        firstclickedflag = false;
        $scope.rightanswerflag = true;
        $timeout(countUp, 50);



      compareproblem+=1;

      $rootScope.levelspeed = compareproblem * 180/$scope.timer;
      if($rootScope.levelspeed > 100) $rootScope.levelspeed =100;

      $rootScope.levelaccuracy = (compareproblem - levelerrorcount) * 100/compareproblem;
      if($rootScope.levelaccuracy > 100) $rootScope.levelaccuracy =100;
      else if($rootScope.levelaccuracy < 0) $rootScope.levelaccuracy =0;


      var currentdate= new Date();
      var currenttime= currentdate.getTime();
    
      var differenttime= currenttime -nowtime;

      
      nowtime= currenttime;
      $scope.score+=1000;
      

        if(differenttime<=2000){
          $scope.starlists.push(correctcount+1);
          $scope.starlists.push(correctcount+2);
          correctcount+=2;

        } else {
          $scope.starlists.push(correctcount+1);
          correctcount+=1;
        }
      
      
       if(correctcount >=$rootScope.levelTitleList[$rootScope.level - 1].number){
        correctcount=0;
        $scope.starlists=[];
        $localStorage.pauseedflag='0';
          // $localStorage.clear();
          if(Number($localStorage.completedlevel) <= Number($localStorage.level) || !$localStorage.completedlevel){
            if($rootScope.levelspeed == 100 && $rootScope.levelaccuracy == 100){
              $localStorage.completedlevel = Number($localStorage.level)+1;
            }
            
            
          }

          $timeout.cancel(mytimeout);
         

          $localStorage.entershowflag=$scope.entershowflag;
          $localStorage.swipeshowflag=$scope.swipeshowflag;

          reportshowfunc('success');
          // $ionicNativeTransitions.stateGo('reportscreen', {}, {}, {
          //   "type": "slide",
          //   "direction": "left", // 'left|right|up|down', default 'left' (which is like 'next') 
          //   "duration": 500, // in milliseconds (ms), default 400 
          // });
       }
      solutionQueue.shift();
      $scope.denometor111.shift();
      stackSize--;
      makeproblem();
        
      
    }

    var wronganswer= function(){
      // if(correctcount>0){
      //   correctcount-=1;
      // }
      levelerrorcount ++;
      $scope.fiboballFlag = true;
      $timeout(function(){
        angular.element("#fibo_ball").animate({top:28+'%'},100, function(){
            $scope.fiboballFlag = false;
            $timeout(countFiboUp, 50);
            $cordovaVibration.vibrate(100);
        });
      }, 20);   

      
      // $scope.starlists.splice(correctcount,1);
      $scope.answer = '';
      
    }


    // Report Part
  $scope.speedlists = ['img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
  $scope.accuracylists = ['img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
  $scope.reportflag = false;


  var reportshowfunc = function(status){
    $scope.reportflag = true;
    if(status == 'failed'){
      $scope.reportTitlePng = "faliure_title.png";
      $scope.continueFlag = false;
      $scope.speedlists = ['img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
      $scope.accuracylists = ['img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
    } else {
      if(Number($localStorage.completedlevel) > $scope.level){
        $scope.continueFlag = true;
      } else {
        $scope.continueFlag = false;
      }
      
      $scope.reportTitlePng = "success_title.png";
    
    

      if($rootScope.levelspeed == 100){
        $scope.speedlists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png'];
      } else if($rootScope.levelspeed > 75 && $rootScope.levelspeed <= 99){
        $scope.speedlists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png', 'img/report/outline.png'];
      } else if($rootScope.levelspeed > 50 && $rootScope.levelspeed <= 74){
        $scope.speedlists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/outline.png', 'img/report/outline.png'];
      } else if($rootScope.levelspeed > 0 && $rootScope.levelspeed <= 49){
        $scope.speedlists = ['img/report/report_star.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
      }

      if($rootScope.levelaccuracy == 100){
        $scope.accuracylists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png'];
      } else if($rootScope.levelaccuracy > 75 && $rootScope.levelaccuracy <= 99){
        $scope.accuracylists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/report_star.png', 'img/report/outline.png'];
      } else if($rootScope.levelaccuracy > 50 && $rootScope.levelaccuracy <= 74){
        $scope.accuracylists = ['img/report/report_star.png', 'img/report/report_star.png', 'img/report/outline.png', 'img/report/outline.png'];
      } else if($rootScope.levelaccuracy > 0 && $rootScope.levelaccuracy <= 49){
        $scope.accuracylists = ['img/report/report_star.png', 'img/report/outline.png', 'img/report/outline.png', 'img/report/outline.png'];
      }
    }

      $timeout(function(){
        angular.element("#real-report").animate({top:-10+'%'},300, function(){
          angular.element("#real-report").animate({top:0+'%'}, 150);
        });      
      }, 100);
      

  }

  $scope.removereportfunc = function(event){
      angular.element("#real-report").animate({top:10+'%'},150, function(){
          angular.element("#real-report").animate({top:-100+'vh'}, 300, function(){
              $scope.reportflag = false;
              switch(event){
                case "back":

                // $ionicNativeTransitions.stateGo($state.current, {}, {}, {                     
                //   });
                  // $ionicNativeTransitions.enable(false);
                  $state.go($state.current, {}, {reload: true});
                  break;
                case "continue":
                  $rootScope.level +=1;
                  $localStorage.level = $rootScope.level;
                  //  $ionicNativeTransitions.stateGo($state.current, {}, {}, {                     
                  // });
                  // $ionicNativeTransitions.enable(false);
                  $state.go($state.current, {}, {reload: true});
                  break;
                case "exit":
                  $ionicNativeTransitions.stateGo('mapview', {}, {}, {
                        "type": "slide",
                        "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
                        "duration": 500, // in milliseconds (ms), default 400 
                  });
                  break;
              }
          });
      });
    
  }
  


  // $scope.backfunc = function (){
  //   $scope.reportflag = false;
  //   $state.go($state.current, {}, {reload: true});
  //   // $ionicNativeTransitions.stateGo('game', {}, {}, {
  //   //       "type": "slide",
  //   //       "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
  //   //       "duration": 500, // in milliseconds (ms), default 400 
  //   //     });
  // }
  // $scope.continuefunc = function (){
  //   $scope.reportflag = false;
  //   $rootScope.level +=1;
  //   $localStorage.level = $rootScope.level;

  //   $state.go($state.current, {}, {reload: true});
  //   // $ionicNativeTransitions.stateGo('game', {}, {}, {
  //   //       "type": "slide",
  //   //       "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
  //   //       "duration": 500, // in milliseconds (ms), default 400 
  //   //     });
  // }
  // $scope.exitfunc = function (){
  //   $scope.reportflag = false;
  //   $ionicNativeTransitions.stateGo('mapview', {}, {}, {
  //         "type": "slide",
  //         "direction": "right", // 'left|right|up|down', default 'left' (which is like 'next') 
  //         "duration": 500, // in milliseconds (ms), default 400 
  //   });
  // }

    

});




