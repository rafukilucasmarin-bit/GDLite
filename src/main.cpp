#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystem.hpp>
#include <atomic>
#include "Platform.hpp"

using namespace geode::prelude;

namespace {
	std::atomic<bool> g_reduceParticles{true};
	std::atomic<int>  g_particleSkip{2};
}

$on_mod(Loaded) {
	auto mod = Mod::get();

	g_reduceParticles = mod->getSettingValue<bool>("reduce-particles");
	g_particleSkip    = static_cast<int>(mod->getSettingValue<int64_t>("particle-skip"));

	listenForSettingChanges<bool>("reduce-particles", [](bool v) {
		g_reduceParticles = v;
	});
	listenForSettingChanges<int64_t>("particle-skip", [](int64_t v) {
		g_particleSkip = static_cast<int>(v);
	});

	litemac::applyMacTweaks(
		mod->getSettingValue<bool>("prevent-app-nap"),
		mod->getSettingValue<bool>("high-priority")
	);
}

class $modify(LiteParticleSystem, CCParticleSystem) {
	void update(float dt) {
		int skip = g_particleSkip.load();

		if (!g_reduceParticles.load() || skip <= 1 || !PlayLayer::get()) {
			CCParticleSystem::update(dt);
			return;
		}

		if (CCDirector::get()->getTotalFrames() % skip != 0) return;
		CCParticleSystem::update(dt * skip);
	}
};

	void update(float dt) {
		int skip = g_particleSkip.load();

		if (!g_reduceParticles.load() || skip <= 1 || !PlayLayer::get()) {
			CCParticleSystem::update(dt);
			return;
		}

		auto f = m_fields.self();
		f->m_accum += dt;

		if (++f->m_tick < skip) return;

		float total = f->m_accum;
		f->m_tick  = 0;
		f->m_accum = 0.f;
		CCParticleSystem::update(total);
	}
};
