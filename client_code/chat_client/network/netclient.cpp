#include "netclient.h"

#include "../model/data.h"

#include <QNetworkReply>

namespace network{

NetClient::NetClient(model::DataCenter* dataCenter)
    :_dataCenter(dataCenter)
{

}

void NetClient::ping(){
    // 构建请求
    QNetworkRequest httpReq;
    httpReq.setUrl(QUrl(HTTP_URL + "/ping"));

    // 发起请求，接收响应
    QNetworkReply* httpResp = _httpClient.get(httpReq);

    // 由于不可靠的网络，这个响应不直到啥时候能回来，所以设置信号槽
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        if(httpResp->error() != QNetworkReply::NoError){
            // 出错了
            LOG() << "HTTP ping error: " << httpResp->errorString();
            httpResp->deleteLater();
            return;
        }
        // ping成功
        LOG() << "HTTP ping success，response message: " << httpResp->readAll();
        httpResp->deleteLater();
    });

}


}  // end namespace
