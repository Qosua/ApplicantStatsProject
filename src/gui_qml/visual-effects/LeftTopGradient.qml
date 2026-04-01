import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

Canvas {
    anchors.fill: parent
    onPaint: {
        var ctx = getContext("2d")
        ctx.clearRect(0, 0, parent.width, parent.height)
        var cx = width * 0.2
        var cy = -height * 0.1
        var grad = ctx.createRadialGradient(cx, cy, 0, cx, cy, width * 0.35)
        grad.addColorStop(0.0, "rgba(85, 109, 163, 0.5)")
        grad.addColorStop(1.0, "rgba(85, 109, 163, 0.0)")
        ctx.fillStyle = grad
        ctx.fillRect(0, 0, width, height)
    }
}