#pragma once

#include "PatientAlertLevels.h"


class Patient;
class Vitals;


// Strategy interface for computing a Patient's alert level from a new
// Vitals reading. Each disease has its own concrete subclass implementing
// the algorithm specified in the assignment brief.
class AlertLevelStrategy
{
public:
	virtual ~AlertLevelStrategy() = default;
	virtual AlertLevel computeAlertLevel(const Patient& patient, const Vitals& vitals) const = 0;
};


// Default no-op strategy used when a patient's diagnosis does not match a
// known disease. The patient stays on Green regardless of their vitals.
class DefaultAlertStrategy : public AlertLevelStrategy
{
public:
	AlertLevel computeAlertLevel(const Patient& patient, const Vitals& vitals) const override;
};


class CordycepsAlertStrategy : public AlertLevelStrategy
{
public:
	AlertLevel computeAlertLevel(const Patient& patient, const Vitals& vitals) const override;
};


class KepralsAlertStrategy : public AlertLevelStrategy
{
public:
	AlertLevel computeAlertLevel(const Patient& patient, const Vitals& vitals) const override;
};


class AndromedaAlertStrategy : public AlertLevelStrategy
{
public:
	AlertLevel computeAlertLevel(const Patient& patient, const Vitals& vitals) const override;
};
