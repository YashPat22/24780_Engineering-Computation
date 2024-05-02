//
//  PS1_3_CountdownTimerUITestsLaunchTests.m
//  PS1-3-CountdownTimerUITests
//
//  Created by Yash Patawari on 8/30/22.
//

#import <XCTest/XCTest.h>

@interface PS1_3_CountdownTimerUITestsLaunchTests : XCTestCase

@end

@implementation PS1_3_CountdownTimerUITestsLaunchTests

+ (BOOL)runsForEachTargetApplicationUIConfiguration {
    return YES;
}

- (void)setUp {
    self.continueAfterFailure = NO;
}

- (void)testLaunch {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app launch];

    // Insert steps here to perform after app launch but before taking a screenshot,
    // such as logging into a test account or navigating somewhere in the app

    XCTAttachment *attachment = [XCTAttachment attachmentWithScreenshot:XCUIScreen.mainScreen.screenshot];
    attachment.name = @"Launch Screen";
    attachment.lifetime = XCTAttachmentLifetimeKeepAlways;
    [self addAttachment:attachment];
}

@end
