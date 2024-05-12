#pragma once

#include <iostream>
#include <string>

namespace S31::Sdc::Test::InputData
{

namespace
{
const char* SmallDeviceMdib = R"(<?xml version="1.0" encoding="UTF-8"?>
<m:GetMdibResponse xmlns:m="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" xmlns:d="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" xmlns:x="http://www.w3.org/2001/XMLSchema-instance" xmlns:e="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" MdibVersion="1" SequenceId="urn:uuid:1c906444-6cb3-43a0-a7fd-d8bc478d8f27">
  <m:Mdib MdibVersion="1" SequenceId="urn:uuid:1c906444-6cb3-43a0-a7fd-d8bc478d8f27">
    <d:MdDescription>
      <d:Mds Handle="md0" SafetyClassification="Inf">
        <d:Type Code="11073" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
        <d:ProductionSpecification>
          <d:SpecType Code="68543">
            <d:ConceptDescription Lang="en-US">Private Coding Semantics</d:ConceptDescription>
          </d:SpecType>
          <d:ProductionSpec>urn:oid:1.3.6.1.4.1.3592.2.1.2.1</d:ProductionSpec>
        </d:ProductionSpecification>
        <d:AlertSystem SafetyClassification="MedA" Handle="Asy.mds0" SelfCheckPeriod="PT5S">
          <d:AlertCondition Handle="0xD3C00100" SafetyClassification="MedA" Kind="Oth" Priority="Me">
            <d:Type Code="199680">
              <d:ConceptDescription Lang="en-US">Apnea by different or undefined sources</d:ConceptDescription>
            </d:Type>
            <d:Source>3569</d:Source>
          </d:AlertCondition>
          <d:AlertSignal Handle="0xD3C00100.loc.Aud" ConditionSignaled="0xD3C00100" Manifestation="Aud" Latching="true"/>
        </d:AlertSystem>
        <d:SystemContext Handle="_contextHandlemd0">
          <d:PatientContext Handle="_patientHandlemd0"/>
          <d:LocationContext Handle="_locationHandlemd0"/>
          <d:EnsembleContext Handle="_ensembleHandlemd0"/>
        </d:SystemContext>
        <d:Sco Handle="Sco.mds0">
          <d:Operation Handle="SVO.37.Asy.mds0" x:type="d:ActivateOperationDescriptor" SafetyClassification="MedC" OperationTarget="md0" MaxTimeToFinish="PT1S" Retriggerable="false" AccessLevel="Usr">
            <d:Type Code="128284">
              <d:ConceptDescription Lang="en-US">An operation to initiate global all audio pause</d:ConceptDescription>
            </d:Type>
          </d:Operation>
          <d:Operation Handle="SVO.38.Asy.mds0" x:type="d:ActivateOperationDescriptor" SafetyClassification="MedC" OperationTarget="md0" MaxTimeToFinish="PT1S" Retriggerable="false" AccessLevel="Usr">
            <d:Type Code="128285">
              <d:ConceptDescription Lang="en-US">An operation to cancel global all audio off</d:ConceptDescription>
            </d:Type>
          </d:Operation>
        </d:Sco>
        <d:Vmd Handle="2435" SafetyClassification="Inf">
          <d:Type Code="69798" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
          <d:ProductionSpecification>
            <d:SpecType Code="67874" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            <d:ProductionSpec>1</d:ProductionSpec>
          </d:ProductionSpecification>
          <d:Channel Handle="2444" SafetyClassification="Inf">
            <d:Type Code="70679" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            <d:ProductionSpecification>
              <d:SpecType Code="67854" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:ProductionSpec>1</d:ProductionSpec>
            </d:ProductionSpecification>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_I" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131841" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
          </d:Channel>
          <d:Channel Handle="2436" SafetyClassification="Inf">
            <d:Type Code="69787" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_DERIVED_V6" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131948" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_DERIVED_V4" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131946" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_DERIVED_V3" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131945" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_DERIVED_V1" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131943" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_V6" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131848" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_V5" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131847" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_V4" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131846" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_V3" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131845" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_V2" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131844" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_V1" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131843" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_AVL" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131903" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_AVF" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131904" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_AVR" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131902" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_III" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131901" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ST.ST_LEAD_II" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="131842" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="0.0001" x:type="d:NumericMetricDescriptor" Handle="Hemo_ECG.HR" SafetyClassification="Inf" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Ep"/>
                  <m:By Method="Get"/>
                  <m:By Method="Per"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="147842" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="266418" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
            </d:Metric>
            <d:Metric MetricCategory="Msrmt" MetricAvailability="Cont" Resolution="1.0" Handle="rtsa" x:type="d:RealTimeSampleArrayMetricDescriptor" SafetyClassification="Inf" MaxDelayTime="P0Y0M0DT0H3M0.1S" SamplePeriod="P0Y0M0DT0H3M0.005S" DeterminationPeriod="PT30S" LifeTimePeriod="PT02H03M00.130000000S">
              <e:Extension>
                <m:Retrievability>
                  <m:By Method="Strm"/>
                </m:Retrievability>
              </e:Extension>
              <d:Type Code="TYPE_ID_HERE" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:Unit Code="264338" CodingSystem="urn:oid:1.3.6.1.4.1.19376.1.6.7.1"/>
              <d:TechnicalRange Lower="0" Upper="100" StepWidth="1"/>
            </d:Metric>
          </d:Channel>
        </d:Vmd>
      </d:Mds>
    </d:MdDescription>
    <d:MdState>
    </d:MdState>
  </m:Mdib>
</m:GetMdibResponse>
)";
}

/**
 * @brief Generates a stream that provides a reasonably small MDIB to be used with integration tests.
 */
inline std::istringstream smallMdib()
{
    return std::istringstream{std::string{SmallDeviceMdib}};
}

}
