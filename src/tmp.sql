SELECT ar.requestID
FROM accommodation_requests ar
WHERE ar.status = '待审批'
ORDER BY ar.requestTime DESC;