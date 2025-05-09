```python
python mktransformer.py
```
## 📊 Gaudi Functional Framework — Functional Types Overview

| **Functional Type**     | **Description**                                                                                      | **Examples**                                                                                                                                       |
|:------------------------|:-----------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------|
| **Consumer**              | One input, no output.                                                                                 | `Rec/RecAlgs`: `EventTimeMonitor`, `ProcStatusAbortMoni`, `TimingTuple`                                                                             |
| **Producer**              | No input, one or more outputs. Used for file I/O, constant data.                                       | *(no specific examples listed)*                                                                                                                     |
| **FilterPredicate**       | No input, one output of True/False only.                                                              | `Phys/LoKiHlt`: `HDRFilter`, `L0Filter`, `ODINFilter`  <br> `Phys/LoKiGen`: `MCFilter`  <br> `Hlt/HltDAQ`: `HltRoutingBitsFilter`  <br> `Rec/LumiAlgs`: `FilterFillingScheme`, `FilterOnLumiSummary` |
| **Transformer**           | One or more inputs, one output.                                                                        | *(no specific examples listed)*                                                                                                                     |
| **MultiTransformer**      | One or more inputs, more than one output.                                                              | *(no specific examples listed)*                                                                                                                     |
| **MergingTransformer**    | Identical inputs, one output.                                                                          | `Calo/CaloPIDs`: `InCaloAcceptanceAlg`  <br> `Tr/TrackUtils`: `TrackListMerger`                                                                     |
| **SplittingTransformer**  | One input, identical outputs.                                                                           | `Hlt/HltDAQ`: `HltRawBankDecoderBase`                                                                                                                |
| **ScalarTransformer**     | Converts a scalar transformation to a vector one. 1:1 mapping applied element-wise to vectors.         | `Calo/CaloReco`: `CaloElectronAlg`, `CaloSinglePhotonAlg`                                                                                           |
