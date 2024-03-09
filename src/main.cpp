#include <Geode/Geode.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/CCSprite.hpp>

using namespace geode::prelude;

class $modify(FMODAudioEngine) {
	TodoReturn loadMusic(gd::string p0, float p1, float p2, float p3, bool p4, int p5, int p6) {
		if(p0 == "menuLoop.mp3") {
			return this->FMODAudioEngine::loadMusic("myMenuLoop.mp3"_spr, p1, p2, p3, p4, p5, p6);
		}
		return this->FMODAudioEngine::loadMusic(p0, p1, p2, p3, p4, p5, p6);
	}

	TodoReturn playMusic(gd::string p0, bool p1, float p2, int p3) {
		if(p0 == "menuLoop.mp3") {
			return this->FMODAudioEngine::playMusic("myMenuLoop.mp3"_spr, p1, p2, p3);
		}
		return this->FMODAudioEngine::playMusic(p0, p1, p2, p3);
	}
};

class $modify(MenuLayer) {
	void onQuit(CCObject* sender) {
		FLAlertLayer::create(
			"Info",
			"You <cr>GONNA</c> play Geometry Dash!\nI'm evil, MUHAHAHAHAHA!",
			"Ok, nevermind"
		)->show();
	}
};

class $modify(LevelInfoLayer) {
	void onDelete(CCObject* sender) {
		if(Mod::get()->getSettingValue<bool>("break-delete")) {
			FLAlertLayer::create(
				"Error",
				"You <cr>CAN'T</c> do that!",
				"nah"
			)->show();
		} else {
			LevelInfoLayer::onDelete(sender);
		}
	}
};

class $modify(CCSprite) {
	static CCSprite* createWithSpriteFrameName(char const* pszSpriteFrameName) {
		if(std::strcmp(pszSpriteFrameName, "GJ_logo_001.png") == 0) {
			return CCSprite::create("my_GJ_logo_001.png"_spr);
		}
		return CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
	}
};