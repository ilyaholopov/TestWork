//
//  UIHelpers.swift
//  TestWork
//
//  Created by Илья Холопов on 07.09.2023.
//

import UIKit

extension UIImage {
    static func imageByMergingImages(topImage: UIImage, bottomImage: UIImage, scaleForTop: CGFloat = 1.0) -> UIImage {
        let size = bottomImage.size
        let container = CGRect(x: 0, y: 0, width: size.width, height: size.height)
        UIGraphicsBeginImageContextWithOptions(size, false, 2.0)
        UIGraphicsGetCurrentContext()!.interpolationQuality = .high
        bottomImage.draw(in: container)

        let topWidth = size.width - 40
        let topHeight = size.height - 40
        let topX = (size.width / 2.0) - (topWidth / 2.0)
        let topY = (size.height / 2.0) - (topHeight / 2.0) - 8

        topImage.draw(in: CGRect(x: topX, y: topY, width: topWidth, height: topHeight), blendMode: .normal, alpha: 1.0)
        return UIGraphicsGetImageFromCurrentImageContext()!
    }
        
    public func cropImageToCircle() -> UIImage? {        
        let sideLength = min(
            size.width,
            size.height
        )
        
        let xOffset = (size.width - sideLength) / 2.0
        let yOffset = (size.height - sideLength) / 2.0
        
        let cropRect = CGRect(
            x: xOffset,
            y: yOffset,
            width: sideLength,
            height: sideLength
        ).integral
        
        let imageRendererFormat = self.imageRendererFormat
        imageRendererFormat.opaque = false
        
        let circleCroppedImage = UIGraphicsImageRenderer(
            size: cropRect.size,
            format: imageRendererFormat).image { context in
                
                let drawRect = CGRect(
                    origin: .zero,
                    size: cropRect.size
                )
                
                UIBezierPath(ovalIn: drawRect).addClip()
                
                let drawImageRect = CGRect(
                    origin: CGPoint(
                        x: -xOffset,
                        y: -yOffset
                    ),
                    size: size
                )
                draw(in: drawImageRect)
            }
        return circleCroppedImage
        
    }
}
