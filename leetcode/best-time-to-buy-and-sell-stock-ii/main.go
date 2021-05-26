func maxProfit(prices []int) int {
    
    out := 0

    holding := false
    var buyPrice int
    for i := 0; i < len(prices); i++ {
        
        var leftHint, rightHint bool

        if holding {

            // previous day price is lower.
            // no need to consider i == 0 case since we are not holding to start with.
            leftHint = prices[i - 1] < prices[i]

            if i == (len(prices) - 1) {
                // already last day. time to sell.
                rightHint = true
            } else {
                // next day price is no higher.
                rightHint = prices[i + 1] <= prices[i]
            }

            // At a local maximum where price is lower before but no higher after, we should sell.
            if leftHint && rightHint {
                // sell.
                out += prices[i] - buyPrice
                holding = false
            }

        } else {
            if i == 0 {
                // no previous day info.
                leftHint = true
            } else {
                // previous day price is not lower.
                leftHint = prices[i - 1] >= prices[i]  
            }

            if i == (len(prices) - 1) {
                // no point buying on last day.
                rightHint = false
            } else {
                // next day price is higher.
                rightHint = prices[i + 1] > prices[i]
            }

            // At a local minimum where price is no lower before but higher after, we should buy.
            if leftHint && rightHint {
                // buy.
                buyPrice = prices[i]
                holding = true
            }
        }
    }
    
    return out
}
