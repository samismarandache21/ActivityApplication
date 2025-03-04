#pragma once
#include "ActivitateService.h"

class UI
{
private:
	ActivitateService& service;
public:

	void print_menu();
	void UIadd();
	void UIdelete();
	void UImodify();
	void UIprint();
	void UIfiltrare();
	void UIsort();
	void UIfind();
	void run_all();
	void itinerar_add();
	void generate_itinerar();
	void export_itinerar();
	void empty_itinerar();
	void print_itinerar();
	void undo();

	UI(ActivitateService& given_service) noexcept;

	void run();

	~UI() noexcept = default;
};

