#include "AlertLevelStrategy.h"

#include "Patient.h"
#include "Vitals.h"


AlertLevel DefaultAlertStrategy::computeAlertLevel(const Patient& /*patient*/, const Vitals& /*vitals*/) const
{
	return AlertLevel::Green;
}


AlertLevel CordycepsAlertStrategy::computeAlertLevel(const Patient& /*patient*/, const Vitals& vitals) const
{
	const int rr = vitals.RR();
	if (rr > 40) return AlertLevel::Red;
	if (rr > 30) return AlertLevel::Orange;
	if (rr > 20) return AlertLevel::Yellow;
	return AlertLevel::Green;
}


AlertLevel KepralsAlertStrategy::computeAlertLevel(const Patient& patient, const Vitals& vitals) const
{
	const int hr = vitals.HR();
	const int age = patient.age();
	if (age < 12 && hr > 120) return AlertLevel::Red;
	if (age >= 12 && hr > 100) return AlertLevel::Red;
	return AlertLevel::Green;
}


AlertLevel AndromedaAlertStrategy::computeAlertLevel(const Patient& /*patient*/, const Vitals& vitals) const
{
	const int bp = vitals.BP();
	if (bp > 140) return AlertLevel::Red;
	if (bp > 130) return AlertLevel::Orange;
	if (bp > 110) return AlertLevel::Yellow;
	return AlertLevel::Green;
}
