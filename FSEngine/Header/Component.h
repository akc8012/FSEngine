#pragma once
#include "ComponentType.h"
#include "FSDebug.h"
#include "FSException.h"
#include "INameable.h"

#include <nlohmann\json.hpp>
using json = nlohmann::json;

#include <string>
#include <memory>
using std::string;
using std::to_string;
using std::unique_ptr;
using std::make_unique;

class Component : public INameable
{
private:
	string name;
	bool serializable = true;

public:
	virtual ~Component();

	static const Types::ComponentType ComponentTypeId = Types::Component;
	virtual Types::ComponentType GetComponentTypeId() const;

	const string& GetName() const override;
	void SetName(const string& name) override;

	virtual json GetJson() const;
	virtual void SetFromJson(const json& j);

	void SetSerializable(bool serializable);
	bool GetSerializable() const;
};
