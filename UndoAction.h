#pragma once
#include "ActivitateRepo.h"

class UndoAction {
protected:
	ActivitateRepo& undo_repo;
	Activitate prev_act;
public:
	UndoAction(ActivitateRepo& repo, const Activitate& act) noexcept : undo_repo{ repo }, prev_act{ act } {}

	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class AddUndo : public UndoAction {
public: 
	AddUndo(ActivitateRepo& repo, const Activitate& act) noexcept : UndoAction(repo, act) {}
	void doUndo() override {
		undo_repo.sterge(prev_act.get_titlu());
	}
};

class RemoveUndo : public UndoAction {
public:
	RemoveUndo(ActivitateRepo& repo, const Activitate& act) noexcept : UndoAction(repo, act) {}
	void doUndo() override {
		undo_repo.adauga(prev_act);
	}
};

class UpdateUndo : public UndoAction {
public:
	UpdateUndo(ActivitateRepo& repo, const Activitate& act) noexcept : UndoAction(repo, act) {}
	void doUndo() override {
		undo_repo.modifica(prev_act.get_titlu(), prev_act);
	}
};