//
//  Assignment_2_Problem_2UITestsLaunchTests.m
//  Assignment 2_Problem 2UITests
//
//  Created by Yash Patawari on 9/10/22.
//

#import <XCTest/XCTest.h>

@interface Assignment_2_Problem_2UITestsLaunchTests : XCTestCase

@end

@implementation Assignment_2_Problem_2UITestsLaunchTests

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
