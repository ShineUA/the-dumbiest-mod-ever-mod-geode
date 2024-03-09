#include <Geode/Geode.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

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

class $modify(MyMenuLayer, MenuLayer) {
	void myClose(CCObject* sender) {
		FLAlertLayer::create(
			"Info",
			"You <cr>GONNA</c> play Geometry Dash!\nI'm evil, MUHAHAHAHAHA!",
			"Ok, nevermind"
		)->show();
	}

	bool init() {
		if(!MenuLayer::init()) return false;
		
		auto logo = this->getChildByID("main-title");
		logo->setVisible(false);

		auto trash_sprite = CCSprite::create("my_GJ_logo_001.png"_spr);
		trash_sprite->setPosition(logo->getPosition());
		this->addChild(trash_sprite);

		auto exitbtn = this->getChildByID("close-menu")->getChildByID("close-button");
		if(exitbtn != nullptr) {
			exitbtn->setVisible(false);
			auto exitSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
			exitSpr->setScale(0.7);
			auto myExitBtn = CCMenuItemSpriteExtra::create(
				exitSpr,
				this,
				menu_selector(MyMenuLayer::myClose)
			);
			myExitBtn->setPosition(exitbtn->getPosition());
			this->getChildByID("close-menu")->addChild(myExitBtn);
		}

		return true;
	}
};

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	void onMyDelete(CCObject* sender) {
		FLAlertLayer::create(
			"Error",
			"You <cr>CAN'T</c> do that!",
			"nah"
		)->show();
	}
	
	bool init(GJGameLevel* p0, bool p1) {
		if(!LevelInfoLayer::init(p0, p1)) return false;

		if(Mod::get()->getSettingValue<bool>("break-delete")) {
			auto delete_btn = this->getChildByID("right-side-menu")->getChildByID("delete-button");
			if(delete_btn != nullptr) {
				delete_btn->setVisible(false);
				auto deleteSpr = CCSprite::createWithSpriteFrameName("GJ_deleteBtn_001.png");
				auto deleteBtn = CCMenuItemSpriteExtra::create(
					deleteSpr,
					this,
					menu_selector(MyLevelInfoLayer::onMyDelete)
				);
				deleteBtn->setPosition(delete_btn->getPosition());
				this->getChildByID("right-side-menu")->addChild(deleteBtn);
			}
		}
		

		return true;
	}
};