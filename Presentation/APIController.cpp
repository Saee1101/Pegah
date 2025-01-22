// #include "APIController.h"



// APIController::APIController(QObject *parent)
//    : Application(parent)
// {
// }

// // void APIController::getData(Context *c)
// // {
// //     QSqlTableModel *model =businessLogic->dbtools->GetAll();
// //     QJsonArray jsonArray;

// //     for (int i = 0; i < model->rowCount(); ++i) {
// //         QJsonObject obj;
// //         obj["id"] = model->data(model->index(i, 0)).toInt();
// //         obj["key"] = model->data(model->index(i, 1)).toString();
// //         obj["value"] = model->data(model->index(i, 2)).toDouble();
// //         jsonArray.append(obj);
// //     }

// // c->response()->setJsonArrayBody(jsonArray);
// // }

// void APIController::getData(Context *c)
// {
//     QSqlTableModel *model =businessLogic->dbtools->GetAll();
//     QJsonArray jsonArray;
//     for (int i = 0; i < model->rowCount(); ++i) {
//         QJsonObject obj;
//         obj["id"] = model->data(model->index(i, 0)).toInt();
//         obj["key"] = model->data(model->index(i, 1)).toString();
//         obj["value"] = model->data(model->index(i, 2)).toDouble();
//         jsonArray.append(obj);
//     }
//     c->response()->setJsonArrayBody(jsonArray);
//     // c->response()->setBody(jsonArray);
//     // c->response()->setJsonObjectBody({
//     //     {QStringLiteral("message"), QStringLiteral("GET request handled")}
//     // });
// }


// void APIController::getData(Context *c)
// {
    // QSqlTableModel *model =businessLogic->dbtools->GetAll();
    // QJsonArray jsonArray;
    // for (int i = 0; i < model->rowCount(); ++i) {
    //     QJsonObject obj;
    //     obj["id"] = model->data(model->index(i, 0)).toInt();
    //     obj["key"] = model->data(model->index(i, 1)).toString();
    //     obj["value"] = model->data(model->index(i, 2)).toDouble();
    //     jsonArray.append(obj);
    // }
    // c->response()->setJsonArrayBody(jsonArray);
    // c->response()->setBody(jsonArray);
    // c->response()->setJsonObjectBody({
    //     {QStringLiteral("message"), QStringLiteral("GET request handled")}
    // });
// }


