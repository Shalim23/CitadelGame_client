#include "Internationalization/Text.h"

//cannot be const due to serialization specifics

static FText WaitingForReadinessMessage = FText::FromString("WaitingForReadiness");
static FText IsReadyMessage = FText::FromString("IsReady");
static FText NotReadyMessage = FText::FromString("NotReady");
static FText AllAreReadyMessage = FText::FromString("AllAreReady");
static FText ClientCancelMessage = FText::FromString("ClientCancel");