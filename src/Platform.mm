#import <Foundation/Foundation.h>
#include <pthread.h>
#include <pthread/qos.h>
#include "Platform.hpp"

namespace litemac {

	static id s_activity = nil;

	void applyMacTweaks(bool preventAppNap, bool highPriority) {
		if (preventAppNap && !s_activity) {
			NSActivityOptions opts =
				NSActivityUserInitiatedAllowingIdleSystemSleep | NSActivityLatencyCritical;
			s_activity = [[NSProcessInfo processInfo]
				beginActivityWithOptions:opts
				reason:@"Geometry Dash necesita temporizadores precisos"];
#if !__has_feature(objc_arc)
			[s_activity retain];
#endif
		}

		if (highPriority) {
			pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);
		}
	}

}
